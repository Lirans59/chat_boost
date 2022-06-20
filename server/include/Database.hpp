#ifndef DATABASE_HPP
#define DATABASE_HPP

#pragma once

#include <iostream>
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/VariadicBind.h"

class Database
{
public:
    Database(const char *file);
    ~Database();
    void add(std::string& user);
    void remove(std::string& username);
    bool valid(std::string& username, std::string& password);

private:
    const char*         _file;
    SQLite::Database    _db;
    // SQLite::Statement   _query;
};

#endif // DATABASE_HPP