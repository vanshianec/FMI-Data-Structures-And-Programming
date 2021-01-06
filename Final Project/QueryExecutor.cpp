#ifndef _QUERY_EXECUTOR_CPP
#define _QUERY_EXECUTOR_CPP

#include <iostream>
#include <map>
#include "QueryExecutor.h"

void QueryExecutor::execute(SelectQuery& selectQuery)
{
    openTableFile(&selectQuery);
    int columnsSize = readColumnsSize();

    const std::vector<std::string> queryColumnNames = selectQuery.getColumnNames();
    if (columnsSize < queryColumnNames.size())
    {
        std::cout << "Selected columns are more than table columns count";
        fileStream.close();
        return;
    }

    const std::string whereColumn = selectQuery.getWhereColumn();
    std::vector<TokenType> columnTypes;
    std::vector<std::string> columnNames;
    int whereColumnIndex = readTableColumns(columnsSize, whereColumn, columnTypes, columnNames);
    if (whereColumnIndex == -1 && !whereColumn.empty())
    {
        std::cout << "There is no such column: [" << whereColumn << "] in the table";
        fileStream.close();
        return;
    }

    if (!validateQueryColumnNames(queryColumnNames, columnNames))
    {
        return;
    }
    readPrimaryKey();

    if (whereColumnIndex != -1)
    {

    }


}

bool QueryExecutor::validateQueryColumnNames(const std::vector<std::string>& queryColumnNames,
                                             const std::vector<std::string>& columnNames) const
{
    if (queryColumnNames[0] == "*")
    {
        return true;
    }

    for (int i = 0; i < queryColumnNames.size(); i++)
    {
        bool columnExists = false;
        for (int j = 0; j < columnNames.size(); j++)
        {
            if (queryColumnNames[i] == columnNames[j])
            {
                columnExists = true;
                break;
            }
        }

        if (!columnExists)
        {
            std::cout << "There is no such column: [" << queryColumnNames[i] << "] in the table" << std::endl;
            return false;
        }
    }

    return true;
}


void QueryExecutor::execute(CreateTableQuery& createTableQuery)
{
    const std::string tableName = createTableQuery.getTableName();
    const std::vector<std::string> columnNames = createTableQuery.getColumnNames();
    const std::vector<TokenType> columnTypes = createTableQuery.getColumnTypes();
    const std::string primaryKey = createTableQuery.getPrimaryKey();
    fileStream.open(tableName + ".dat", std::ios::out | std::ios::binary);

    int columnsSize = columnNames.size();
    fileStream.write((char*) &columnsSize, sizeof(columnsSize));

    for (int i = 0; i < columnsSize; i++)
    {
        fileStream.write((char*) &columnTypes[i], sizeof(TokenType));
        int columnNameLength = columnNames[i].length();
        fileStream.write((char*) &columnNameLength, sizeof(columnNameLength));
        fileStream.write(columnNames[i].c_str(), columnNameLength);
    }

    int primaryKeyLength = primaryKey.length();
    fileStream.write((char*) &primaryKeyLength, sizeof(primaryKeyLength));
    fileStream.write(primaryKey.c_str(), primaryKeyLength);
    fileStream.close();
}

void QueryExecutor::execute(CreateIndexQuery&)
{
    //TODO
}

void QueryExecutor::execute(InsertQuery& insertQuery)
{
    if (!openTableFile(&insertQuery))
    {
        std::cout << "Cannot open table file";
        return;
    }

    int columnsSize = readColumnsSize();
    const std::vector<Scanner::Token> columnValues = insertQuery.getColumnValues();

    if (columnsSize != columnValues.size())
    {
        std::cout << "Arguments count doesn't match table columns count";
        fileStream.close();
        return;
    }

    std::vector<TokenType> columnTypes;
    if (!readColumnsTypes(columnsSize, columnValues, columnTypes))
    {
        return;
    }

    fileStream.seekp(0, std::ios_base::end);

    for (int i = 0; i < columnsSize; i++)
    {
        std::string columnValue = columnValues[i].value;
        TokenType columnType = columnTypes[i];
        writeColumnArgument(columnValue, columnType);
    }

    fileStream.close();
}

bool QueryExecutor::readColumnsTypes(int columnsSize, const std::vector<Scanner::Token>& columnValues,
                                     std::vector<TokenType>& columnTypes)
{
    TokenType columnType;
    int columnNameLength;
    for (int i = 0; i < columnsSize; i++)
    {
        std::string columnName;
        fileStream.read((char*) &columnType, sizeof(TokenType));
        fileStream.read((char*) &columnNameLength, sizeof(columnNameLength));
        columnName.resize(columnNameLength);
        fileStream.read(&columnName[0], columnNameLength);
        if (!validateArgumentType(columnValues, columnType, i, columnName))
        {
            fileStream.close();
            return false;
        }
        columnTypes.push_back(columnType);
    }

    return true;
}

int QueryExecutor::readColumnsSize()
{
    int columnsSize;
    fileStream.read((char*) &columnsSize, sizeof(columnsSize));
    return columnsSize;
}

bool QueryExecutor::openTableFile(const Query* query)
{
    const std::string tableName = query->getTableName();
    fileStream.open(tableName + ".dat", std::ios::binary);
    return (bool) fileStream;
}

void QueryExecutor::execute(UpdateQuery& updateQuery)
{
    openTableFile(&updateQuery);
    int columnsSize = readColumnsSize();

    const std::vector<Scanner::Token> queryColumnValues = updateQuery.getColumnValues();
    if (columnsSize < queryColumnValues.size())
    {
        std::cout << "Column arguments are more than table columns count";
        fileStream.close();
        return;
    }

    const std::string whereColumn = updateQuery.getWhereColumn();

    std::vector<TokenType> columnTypes;
    std::vector<std::string> columnNames;
    int whereColumnIndex = readTableColumns(columnsSize, whereColumn, columnTypes, columnNames);
    if (whereColumnIndex == -1)
    {
        std::cout << "There is no such column: [" << whereColumn << "] in the table";
        fileStream.close();
        return;
    }

    const std::vector<std::string> queryColumnNames = updateQuery.getColumnNames();
    std::map<int, std::string> queryColumnNamesByPosition;
    std::map<int, Scanner::Token> queryColumnValuesByPosition;

    if (!validateQueryColumnArguments(queryColumnValues, queryColumnNames, columnTypes, columnNames,
                                      queryColumnNamesByPosition,
                                      queryColumnValuesByPosition))
    {
        return;
    }

    readPrimaryKey();
    const Scanner::Token whereValue = updateQuery.getWhereValue();
    const TokenType whereOp = updateQuery.getOp();
    updateRows(columnsSize, whereValue, whereOp, columnTypes, whereColumnIndex, queryColumnNamesByPosition,
               queryColumnValuesByPosition);
    fileStream.close();
}

void QueryExecutor::updateRows(int columnsSize, const Scanner::Token& whereValue, const TokenType& whereOp,
                               const std::vector<TokenType>& columnTypes, int whereColumnIndex,
                               std::map<int, std::string>& queryColumnNamesByPosition,
                               std::map<int, Scanner::Token>& queryColumnValuesByPosition)
{
    int updatedRows = 0;
    while (!fileStream.eof())
    {
        int pos = fileStream.tellg();
        for (int i = 0; i < columnsSize; i++)
        {
            std::string columnValue = readColumnValue(columnTypes[i]);
            if (i == whereColumnIndex && isWhereConditionMet(columnValue, whereOp, whereValue, columnTypes[i]))
            {
                fileStream.seekp(pos);
                for (int j = 0; j < columnsSize; j++)
                {
                    if (queryColumnNamesByPosition.find(j) == queryColumnNamesByPosition.end())
                    {
                        readColumnValue(columnTypes[j]);
                    }
                    else
                    {
                        Scanner::Token queryColumnValue = queryColumnValuesByPosition[j];
                        writeColumnArgument(queryColumnValue.value, queryColumnValue.type);
                        updatedRows++;
                    }
                }

                break;
            }
        }
    }

    std::cout << updatedRows << " rows updated" << std::endl;
}

void QueryExecutor::readPrimaryKey()
{
    int primaryKeyLength;
    fileStream.read((char*) &primaryKeyLength, sizeof(primaryKeyLength));
    std::string primaryKey;
    primaryKey.resize(primaryKeyLength);
    fileStream.read(&primaryKey[0], primaryKeyLength);
}

bool QueryExecutor::validateQueryColumnArguments(const std::vector<Scanner::Token>& queryColumnValues,
                                                 const std::vector<std::string>& queryColumnNames,
                                                 const std::vector<TokenType>& columnTypes,
                                                 const std::vector<std::string>& columnNames,
                                                 std::map<int, std::string>& queryColumnNamesByPosition,
                                                 std::map<int, Scanner::Token>& queryColumnValuesByPosition) const
{
    for (int i = 0; i < queryColumnNames.size(); i++)
    {
        bool columnExists = false;
        for (int j = 0; j < columnNames.size(); j++)
        {
            if (queryColumnNames[i] == columnNames[j])
            {
                if (queryColumnValues[i].type != columnTypes[j])
                {
                    std::cout << "Query column type doesn't match the table column type ... exp, act";
                    return false;
                }
                columnExists = true;
                queryColumnNamesByPosition[j] = queryColumnNames[i];
                queryColumnValuesByPosition[j] = queryColumnValues[i];
                break;
            }
        }

        if (!columnExists)
        {
            std::cout << "There is no such column: [" << queryColumnNames[i] << "] in the table";
            return false;
        }
    }

    return true;
}

bool isWhereConditionMet(const std::string& columnValue, const TokenType op, const Scanner::Token& whereValue,
                         const TokenType columnType)
{
    if (whereValue.type != columnType)
    {
        std::cout << "Invalid column type in where clause expected....";
        return false;
    }

    switch (op)
    {
        case EQUAL_OP:
            return areValuesEqual(columnValue, whereValue);
        case LESS_THAN_OP:
            return isLessThan(columnValue, whereValue);
        case MORE_THAN_OP:
            return isMoreThan(columnValue, whereValue);
        case LESS_THAN_OR_EQUAL_OP:
            return areValuesEqual(columnValue, whereValue) || isLessThan(columnValue, whereValue);
        case MORE_THAN_OR_EQUAL_OP:
            return areValuesEqual(columnValue, whereValue) || isMoreThan(columnValue, whereValue);
    }

    return false;
}

bool isMoreThan(const std::string& columnValue, const Scanner::Token& whereValue)
{
    switch (whereValue.type)
    {
        case INT:
            return std::stoi(columnValue) > std::stoi(whereValue.value);
        case DOUBLE:
            return std::stod(columnValue) > std::stoi(whereValue.value);
        case BOOL:
            return columnValue == "1" && whereValue.value == "0";
        case STRING:
            return columnValue.compare(whereValue.value) > 0;
    }
}

bool isLessThan(const std::string& columnValue, const Scanner::Token& whereValue)
{
    switch (whereValue.type)
    {
        case INT:
            return std::stoi(columnValue) < std::stoi(whereValue.value);
        case DOUBLE:
            return std::stod(columnValue) < std::stoi(whereValue.value);
        case BOOL:
            return columnValue == "0" && whereValue.value == "1";
        case STRING:
            return columnValue.compare(whereValue.value) < 0;
    }
}

bool areValuesEqual(const std::string& columnValue, const Scanner::Token& whereValue)
{
    return columnValue == whereValue.value;
}

int
QueryExecutor::readTableColumns(int columnsSize, const std::string& whereColumn, std::vector<TokenType>& columnTypes,
                                std::vector<std::string>& columnNames)
{
    int whereColumnIndex = -1;

    for (int i = 0; i < columnsSize; i++)
    {
        TokenType columnType;
        int columnNameLength;
        std::string columnName;

        fileStream.read((char*) &columnType, sizeof(TokenType));
        fileStream.read((char*) &columnNameLength, sizeof(columnNameLength));
        columnName.resize(columnNameLength);
        fileStream.read(&columnName[0], columnNameLength);
        if (columnName == whereColumn)
        {
            whereColumnIndex = i;
        }

        columnNames.push_back(columnName);
        columnTypes.push_back(columnType);
    }

    return whereColumnIndex;
}

void QueryExecutor::writeColumnArgument(const std::string& columnValue, const TokenType& columnType)
{
    if (columnType == INT)
    {
        int intValue = std::stoi(columnValue);
        fileStream.write((char*) &intValue, sizeof(intValue));
    }
    else if (columnType == DOUBLE)
    {
        double doubleValue = std::stod(columnValue);
        fileStream.write((char*) &doubleValue, sizeof(doubleValue));
    }
    else if (columnType == BOOL)
    {
        bool boolValue = columnValue == "1";
        fileStream.write((char*) &boolValue, sizeof(boolValue));
    }
    else if (columnType == STRING)
    {
        int length = columnValue.length();
        fileStream.write((char*) &length, sizeof(length));
        fileStream.write(columnValue.c_str(), length);
        std::string empty;
        fileStream.write(empty.c_str(), Query::maxStringValueLength - length);
    }
}

std::string QueryExecutor::readColumnValue(const TokenType& columnType)
{
    std::string value;
    if (columnType == INT)
    {
        int intValue;
        fileStream.read((char*) &intValue, sizeof(intValue));
        value = std::to_string(intValue);
    }
    else if (columnType == DOUBLE)
    {
        double doubleValue;
        fileStream.read((char*) &doubleValue, sizeof(doubleValue));
        value = std::to_string(doubleValue);
    }
    else if (columnType == BOOL)
    {
        bool boolValue;
        fileStream.read((char*) &boolValue, sizeof(boolValue));
        value = std::to_string(boolValue);
    }
    else if (columnType == STRING)
    {
        int length;
        fileStream.read((char*) &length, sizeof(length));
        std::string stringValue;
        stringValue.resize(length);
        fileStream.read(&stringValue[0], length);
        int emptyValueLength = Query::maxStringValueLength - length;
        std::string emptyValue;
        emptyValue.resize(emptyValueLength);
        fileStream.read(&emptyValue[0], emptyValueLength);
        value = stringValue;
    }

    return value;
}

bool validateArgumentType(const std::vector<Scanner::Token>& columnValues, const TokenType& columnType,
                          int index, const std::string& columnName)
{
    if (columnType != columnValues[index].type)
    {
        std::cout << "Invalid argument [" << columnValues[index].value << "] for column : " << columnName
                  << "! Expected type: " << columnType << ", Provided type: " << columnValues[index].type << std::endl;
    }
}

#endif