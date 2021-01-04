cmake_minimum_required(VERSION 3.17)
project(Final_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Final_Project main.cpp Scanner.cpp Parser.cpp Query.cpp CreateTableQuery.cpp InsertQuery.cpp UpdateQuery.cpp SelectQuery.cpp CreateIndexQuery.cpp QueryExecutor.cpp)