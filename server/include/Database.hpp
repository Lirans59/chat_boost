#ifndef DATABASE_HPP
#define DATABASE_HPP

#pragma once

#include <iostream>
#include "SQLiteCpp/SQLiteCpp.h"
#include "SQLiteCpp/VariadicBind.h"

class Database
{
public:
    Database(const char *path);
    ~Database();
    void add(std::string& username, std::string& password);
    void remove(std::string& username);
    bool valid(std::string& username, std::string& password);

private:
    const char*         _path;
    SQLite::Database    _db;
    std::uint32_t       _count;//use AUTOINCREMENT instead
};

#endif // DATABASE_HPP