#ifndef _QUERY_EXECUTOR_CPP
#define _QUERY_EXECUTOR_CPP

#include <iostream>
#include <algorithm>
#include "QueryExecutor.h"

void QueryExecutor::execute(CreateTableQuery& createTableQuery)
{
    const std::string tableName = createTableQuery.getTableName();
    std::vector<Token> columns = createTableQuery.getColumns();
    Token primaryKey = createTableQuery.getPrimaryKey();
    fileStream.open(tableName, std::ios::out | std::ios::binary);

    int columnsSize = columns.size();
    fileStream.write((char*) &columnsSize, sizeof(columnsSize));

    for (int i = 0; i < columnsSize; i++)
    {
        columns[i].write(fileStream);
    }

    primaryKey.write(fileStream);

    std::cout << "Table \"" << tableName << "\" created." << std::endl;
    fileStream.close();
}

void QueryExecutor::execute(InsertQuery& insertQuery)
{
    std::string tableName = insertQuery.getTableName();
    openTableFile(tableName);

    int columnsSize = readColumnsSize();
    const std::vector<Token> insertValues = insertQuery.getInsertValues();

    if (columnsSize != insertValues.size())
    {
        std::cout << "Insert values count doesn't match table columns count" << std::endl;
        fileStream.close();
        return;
    }

    std::vector<TokenType> columnTypes;
    std::vector<std::string> columnNames;
    readTableColumns(columnsSize, insertValues, columnNames, columnTypes);

    Token primaryKey;
    primaryKey.read(fileStream);

    std::set<std::string> primaryKeyValues;
    readPrimaryKeyValues(columnsSize, columnTypes, columnNames, primaryKey, primaryKeyValues);
    checkForDuplicateValue(columnsSize, insertValues, columnNames, primaryKey, primaryKeyValues);
    fileStream.clear();
    fileStream.seekp(0, std::ios_base::end);
    for (int i = 0; i < columnsSize; i++)
    {
        std::string insertValue = insertValues[i].value;
        TokenType columnType = columnTypes[i];
        writeInsertArgument(insertValue, columnType);
    }

    std::cout << "Record inserted." << std::endl;
    fileStream.close();
}

void QueryExecutor::checkForDuplicateValue(int columnsSize, const std::vector<Token>& insertValues,
                                           const std::vector<std::string>& columnNames, const Token& primaryKey,
                                           const std::set<std::string>& primaryKeyValues)
{
    for (int i = 0; i < columnsSize; i++)
    {
        if (primaryKey.value == columnNames[i] &&
            primaryKeyValues.find(insertValues[i].value) != primaryKeyValues.end())
        {
            fileStream.close();
            error("ERROR: Duplicate primary key value. Record NOT inserted");
        }
    }
}

void QueryExecutor::readPrimaryKeyValues(int columnsSize, const std::vector<TokenType>& columnTypes,
                                         const std::vector<std::string>& columnNames, const Token& primaryKey,
                                         std::set<std::string>& primaryKeyValues)
{
    while (true)
    {
        for (int i = 0; i < columnsSize; i++)
        {
            std::string columnValue = readColumnValue(columnTypes[i]);
            if (fileStream.eof())
            {
                return;
            }
            if (primaryKey.value == columnNames[i])
            {
                primaryKeyValues.insert(columnValue);
            }
        }
    }
}

void QueryExecutor::openTableFile(const std::string& tableName)
{
    if (!fileExists(tableName.c_str()))
    {
        error("There is no such table: '" + tableName + "'");
    }

    fileStream.open(tableName, std::ios::in | std::ios::out | std::ios::binary);

    if (!fileStream)
    {
        error("Cannot open file");
    }
}

void error(const std::string& message)
{
    throw std::invalid_argument(message);
}

bool fileExists(const char* fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

int QueryExecutor::readColumnsSize()
{
    int columnsSize;
    fileStream.read((char*) &columnsSize, sizeof(columnsSize));
    return columnsSize;
}

void QueryExecutor::readTableColumns(int columnsSize, const std::vector<Token>& insertValues,
                                     std::vector<std::string>& columnNames, std::vector<TokenType>& columnTypes)
{
    for (int i = 0; i < columnsSize; i++)
    {
        Token currentColumn;
        currentColumn.read(fileStream);
        validateArgumentType(insertValues[i], currentColumn.type, currentColumn.value);
        columnTypes.push_back(currentColumn.type);
        columnNames.push_back(currentColumn.value);
    }
}

void QueryExecutor::validateArgumentType(const Token& currentInsertToken, const TokenType& columnType,
                                         const std::string& columnName)
{
    if (columnType != currentInsertToken.type)
    {
        fileStream.close();
        std::string message = "Invalid argument '" + currentInsertToken.value + "' for column : '"
                              + columnName + "' ! Expected type: ";
        message.append(tokenTypeToString(columnType));
        message.append(", Provided type: ");
        message.append(tokenTypeToString(currentInsertToken.type));
        error(message);
    }
}

void QueryExecutor::writeInsertArgument(const std::string& columnValue, const TokenType& columnType)
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
        writeStringValue(fileStream, columnValue);
    }
}

void writeStringValue(std::fstream& stream, const std::string& columnValue)
{
    int length = columnValue.length();
    stream.write((char*) &length, sizeof(length));
    stream.write(columnValue.c_str(), length);
    std::string empty;
    stream.write(empty.c_str(), Query::maxStringValueLength - length);
}

void QueryExecutor::execute(CreateIndexQuery& createIndexQuery)
{
    const std::string tableName = createIndexQuery.getTableName();
    openTableFile(tableName);
    const std::string columnName = createIndexQuery.getColumnName();

    int columnsSize = readColumnsSize();
    std::vector<std::string> columnNames;
    std::vector<TokenType> columnTypes;
    int columnIndex = findColumnIndex(columnsSize, columnName, columnTypes, columnNames);
    if (columnIndex == -1)
    {
        std::cout << "There is no such column: [" << columnName << "] in the table" << std::endl;
        fileStream.close();
        return;
    }

    Token primaryKey;
    primaryKey.read(fileStream);
    bool isPrimary = columnName == primaryKey.value;

    while (true)
    {
        int pos = fileStream.tellg();
        for (int i = 0; i < columnsSize; i++)
        {
            std::string columnValue = readColumnValue(columnTypes[i]);
            if (fileStream.eof())
            {
                std::cout << "Created index" << std::endl;
                fileStream.close();
                return;
            }
        }
    }
}

void QueryExecutor::execute(UpdateQuery& updateQuery)
{
    const std::string tableName = updateQuery.getTableName();
    openTableFile(tableName);
    int columnsSize = readColumnsSize();

    const std::vector<Token> queryColumnValues = updateQuery.getColumnValues();
    if (columnsSize < queryColumnValues.size())
    {
        std::cout << "Query arguments are more than table columns count" << std::endl;
        fileStream.close();
        return;
    }

    const std::string whereColumn = updateQuery.getWhereColumn();

    std::vector<TokenType> columnTypes;
    std::vector<std::string> columnNames;
    int whereColumnIndex = findColumnIndex(columnsSize, whereColumn, columnTypes, columnNames);
    const Token whereValue = updateQuery.getWhereValue();
    if (!validateWhereColumn(whereColumn, columnTypes, whereColumnIndex, whereValue))
    {
        return;
    }

    const std::vector<std::string> queryColumnNames = updateQuery.getColumnNames();
    std::unordered_map<int, std::string> queryColumnNamesByPosition;
    std::unordered_map<int, Token> queryColumnValuesByPosition;

    if (!validateQueryColumnArguments(queryColumnValues, queryColumnNames, columnTypes, columnNames,
                                      queryColumnNamesByPosition, queryColumnValuesByPosition))
    {
        return;
    }

    Token primaryKey;
    primaryKey.read(fileStream);
    const TokenType whereOp = updateQuery.getOp();
    updateRows(columnsSize, whereValue, whereOp, columnTypes, whereColumnIndex, queryColumnNamesByPosition,
               queryColumnValuesByPosition);
}

bool validateWhereColumn(const std::string& whereColumn, const std::vector<TokenType>& columnTypes,
                         int whereColumnIndex, const Token& whereValue)
{
    if (whereColumnIndex == -1)
    {
        std::cout << "There is no such column: [" + whereColumn + "] in the table" << std::endl;
        return false;
    }
    else if (columnTypes[whereColumnIndex] != whereValue.type)
    {
        std::cout << "Where column type doesn't match expected column type!"
                  << "Expected type: " << tokenTypeToString(columnTypes[whereColumnIndex])
                  << ", Actual type: " << tokenTypeToString(whereValue.type) << std::endl;
        return false;
    }

    return true;
}

bool validateQueryColumnArguments(const std::vector<Token>& queryColumnValues,
                                  const std::vector<std::string>& queryColumnNames,
                                  const std::vector<TokenType>& columnTypes,
                                  const std::vector<std::string>& columnNames,
                                  std::unordered_map<int, std::string>& queryColumnNamesByPosition,
                                  std::unordered_map<int, Token>& queryColumnValuesByPosition)
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
                    std::string message = "Invalid argument '" + queryColumnValues[i].value + "' for column : '"
                                          + columnNames[j] + "' ! Expected type: ";
                    message.append(tokenTypeToString(columnTypes[j]));
                    message.append(", Provided type: ");
                    message.append(tokenTypeToString(queryColumnValues[i].type));
                    std::cout << message << std::endl;
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
            std::cout << "There is no such column: [" << queryColumnNames[i] << "] in the table" << std::endl;
            return false;
        }
    }

    return true;
}

void QueryExecutor::updateRows(int columnsSize, const Token& whereValue, const TokenType& whereOp,
                               const std::vector<TokenType>& columnTypes, int whereColumnIndex,
                               std::unordered_map<int, std::string>& queryColumnNamesByPosition,
                               std::unordered_map<int, Token>& queryColumnValuesByPosition)
{
    int updatedRows = 0;
    while (true)
    {
        int pos = fileStream.tellg();
        for (int i = 0; i < columnsSize; i++)
        {
            std::string columnValue = readColumnValue(columnTypes[i]);
            if (fileStream.eof())
            {
                std::cout << updatedRows << " rows updated." << std::endl;
                fileStream.close();
                return;
            }
            if (i == whereColumnIndex && isWhereConditionMet(columnValue, whereOp, whereValue))
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
                        Token queryColumnValue = queryColumnValuesByPosition[j];
                        writeInsertArgument(queryColumnValue.value, queryColumnValue.type);
                    }
                }
                updatedRows++;
                break;
            }
        }
    }
}

void QueryExecutor::execute(SelectQuery& selectQuery)
{
    openTableFile(selectQuery.getTableName());
    int columnsSize = readColumnsSize();

    const std::vector<std::string> queryColumnNames = selectQuery.getColumnNames();
    if (columnsSize < queryColumnNames.size())
    {
        std::cout << "Selected columns are more than table columns count" << std::endl;
        fileStream.close();
        return;
    }

    const std::string whereColumn = selectQuery.getWhereColumn();
    std::vector<TokenType> columnTypes;
    std::vector<std::string> columnNames;
    const Token whereValue = selectQuery.getWhereValue();
    int whereColumnIndex = findColumnIndex(columnsSize, whereColumn, columnTypes, columnNames);
    if (!whereColumn.empty() && !validateWhereColumn(whereColumn, columnTypes, whereColumnIndex, whereValue))
    {
        return;
    }

    std::unordered_map<int, std::string> queryColumnNamesByPosition;
    if (!validateQueryColumnNames(queryColumnNamesByPosition, queryColumnNames, columnNames))
    {
        return;
    }

    Token primaryKey;
    primaryKey.read(fileStream);

    readRowsToSelect(selectQuery, columnsSize, queryColumnNames, columnTypes, whereValue, whereColumnIndex,
                     queryColumnNamesByPosition);


}

void QueryExecutor::readRowsToSelect(const SelectQuery& selectQuery, int columnsSize,
                                     const std::vector<std::string>& queryColumnNames,
                                     const std::vector<TokenType>& columnTypes, const Token& whereValue,
                                     int whereColumnIndex,
                                     std::unordered_map<int, std::string>& queryColumnNamesByPosition)
{
    TokenType whereOp = selectQuery.getWhereOp();
    std::vector<std::vector<Token>> selectedRows;
    while (true)
    {
        int pos = fileStream.tellg();
        for (int i = 0; i < columnsSize; i++)
        {
            std::string columnValue = readColumnValue(columnTypes[i]);
            if (fileStream.eof())
            {
                if (!selectQuery.getAggregates().empty())
                {
                    aggregateRows(selectQuery.getAggregates(), selectedRows);
                }
                else if (!selectQuery.getOrderByColumn().empty())
                {
                    fileStream.clear();
                    fileStream.seekp(0, std::ios::beg);
                    readColumnsSize();
                    std::vector<std::string> names;
                    std::vector<TokenType> types;
                    int sortColumnIndex = findColumnIndex(columnsSize, selectQuery.getOrderByColumn(), types, names);
                    if (sortColumnIndex == -1)
                    {
                        error("There is no such column: [" + selectQuery.getOrderByColumn() + "]");
                    }
                    //sortRows(sortColumnIndex, selectQuery.getOrderType(), selectedRows);
                }

                printSelectedRows(selectedRows);
                fileStream.close();
                return;
            }

            if (whereColumnIndex == -1 ||
                (whereColumnIndex == i && isWhereConditionMet(columnValue, whereOp, whereValue)))
            {
                fileStream.seekp(pos);
                int rowSize = queryColumnNames[0] == "*" ? columnsSize : queryColumnNames.size();
                std::vector<Token> currentRow(rowSize);
                for (int j = 0; j < columnsSize; j++)
                {
                    columnValue = readColumnValue(columnTypes[j]);
                    Token currentData;
                    currentData.value = columnValue;
                    currentData.type = columnTypes[j];
                    if (queryColumnNames[0] == "*")
                    {
                        currentRow[j] = currentData;
                    }
                    else if (queryColumnNamesByPosition.find(j) != queryColumnNamesByPosition.end())
                    {
                        for (int k = 0; k < queryColumnNames.size(); k++)
                        {
                            if (queryColumnNames[k] == queryColumnNamesByPosition[j])
                            {
                                for (int l = 0; l < queryColumnNames.size(); l++)
                                {
                                    if (queryColumnNames[l] == queryColumnNames[k])
                                    {
                                        currentRow[l] = currentData;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }

                selectedRows.push_back(currentRow);
                break;
            }
        }
    }
}

bool validateQueryColumnNames(std::unordered_map<int, std::string>& queryColumnsByPosition,
                              const std::vector<std::string>& queryColumnNames,
                              const std::vector<std::string>& columnNames)
{
    if (queryColumnNames[0] == "*")
    {
        for (int i = 0; i < queryColumnNames.size(); i++)
        {
            queryColumnsByPosition[i] = queryColumnNames[i];
        }

        return true;
    }

    for (int i = 0; i < queryColumnNames.size(); i++)
    {
        bool columnExists = false;
        for (int j = 0; j < columnNames.size(); j++)
        {
            if (queryColumnNames[i] == columnNames[j])
            {
                queryColumnsByPosition[j] = columnNames[j];
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

void printSelectedRows(const std::vector<std::vector<Token>>& selectedRows)
{
    std::cout << selectedRows.size() << " rows selected." << std::endl;
    for (int i = 0; i < selectedRows.size(); i++)
    {
        std::vector<Token> currentRow = selectedRows[i];
        for (int j = 0; j < currentRow.size(); j++)
        {
            std::cout << currentRow[j].value;
            if (j != currentRow.size() - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << std::endl;
    }
}


bool isWhereConditionMet(const std::string& columnValue, const TokenType& op, const Token& whereValue)
{
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

bool isMoreThan(const std::string& columnValue, const Token& whereValue)
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

    return false;
}

bool isLessThan(const std::string& columnValue, const Token& whereValue)
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

    return false;
}

bool areValuesEqual(const std::string& columnValue, const Token& whereValue)
{
    switch (whereValue.type)
    {
        case INT:
            return std::stoi(columnValue) == std::stoi(whereValue.value);
        case DOUBLE:
            return std::stod(columnValue) == std::stoi(whereValue.value);
    }

    return columnValue == whereValue.value;
}

int
QueryExecutor::findColumnIndex(int columnsSize, const std::string& searchColumn, std::vector<TokenType>& columnTypes,
                               std::vector<std::string>& columnNames)
{
    int index = -1;

    for (int i = 0; i < columnsSize; i++)
    {
        Token currentColumn;
        currentColumn.read(fileStream);
        if (currentColumn.value == searchColumn)
        {
            index = i;
        }

        columnNames.push_back(currentColumn.value);
        columnTypes.push_back(currentColumn.type);
    }

    return index;
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
        if (fileStream.eof())
        {
            return value;
        }
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

void aggregateRows(const std::vector<TokenType>& aggregates, std::vector<std::vector<Token>>& rows)
{
    std::vector<double> aggs(aggregates.size());
    for (int i = 0; i < aggs.size(); i++)
    {
        if (aggregates[i] == MIN || aggregates[i] == MAX)
        {
            aggs[i] = std::stod(rows[0][i].value);
        }
        else
        {
            aggs[i] = 0;
        }
    }

    for (int i = 0; i < rows.size(); i++)
    {
        for (int j = 0; j < rows[i].size(); j++)
        {
            if (rows[i][j].type != INT && rows[i][j].type != DOUBLE)
            {
                error("Invalid aggregate type!");
            }
            else
            {
                double value = std::stod(rows[i][j].value);
                switch (aggregates[j])
                {
                    case MIN:
                        if (value < aggs[j])
                        {
                            aggs[j] = value;
                        }
                        break;
                    case MAX:
                        if (value > aggs[j])
                        {
                            aggs[j] = value;
                        }
                        break;
                    case SUM:
                        aggs[j] += value;
                        break;
                    case COUNT:
                        aggs[j]++;
                        break;
                    case AVG:
                        aggs[j] += value;
                        break;
                }
            }
        }
    }

    int oldRowsSize = rows.size();
    rows.clear();
    std::vector<Token> row(aggs.size());
    for (int i = 0; i < aggs.size(); i++)
    {
        Token token;
        if (aggregates[i] == AVG)
        {
            aggs[i] = aggs[i] / oldRowsSize;
        }
        token.value = std::to_string(aggs[i]);
        row[i] = token;
    }

    rows.push_back(row);
}


#endif

