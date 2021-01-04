#ifndef _QUERY_EXECUTOR_CPP
#define _QUERY_EXECUTOR_CPP

#include <iostream>
#include "QueryExecutor.h"

void QueryExecutor::execute(SelectQuery& selectQuery)
{

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
    const std::string tableName = insertQuery.getTableName();
    const std::vector<Scanner::Token> columnValues = insertQuery.getColumnValues();
    fileStream.open(tableName + ".dat", std::ios::binary);
    int columnsSize;
    fileStream.read((char*) &columnsSize, sizeof(columnsSize));
    if (columnsSize != columnValues.size())
    {
        std::cout << "Arguments count doesn't match table columns count";
        fileStream.close();
        return;
    }

    TokenType columnType;
    int columnNameLength;
    for (int i = 0; i < columnsSize; i++)
    {
        std::string columnName;
        fileStream.read((char*) &columnType, sizeof(TokenType));
        fileStream.read((char*) &columnNameLength, sizeof(columnNameLength));
        columnName.resize(columnNameLength);
        fileStream.read(&columnName[0], columnNameLength);
        if (columnType != columnValues[i].type)
        {
            std::cout << "Invalid argument [" << columnValues[i].value << "] for column : " << columnName
                      << "! Expected type: " << columnType << ", Provided type: " << columnValues[i].type << std::endl;
            fileStream.close();
            return;
        }
    }

    for (int i = 0; i < columnsSize; i++)
    {
        std::string columnValue = columnValues[i].value;
        columnNameLength = columnValue.length();
        //TODO switch which type to write
        /*fileStream.write((char*) &columnNameLength, sizeof(columnNameLength));
        fileStream.write(columnNames[i].c_str(), columnNameLength);*/
    }
}

void QueryExecutor::execute(UpdateQuery&)
{

}

#endif