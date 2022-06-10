#ifndef USERDB_HPP
#define USERDB_HPP

#pragma once

#include <iostream>
#include <fstream>

class UserDB
{
public:
    UserDB(const char *name);
    ~UserDB();
    void add(std::string& user);
    void remove(std::string& username);
    bool valid(std::string& username, std::string& password);

private:
    const char      *_name;
    std::ofstream   _ofile;
    std::ifstream   _ifile;
};

#endif // USERDB_HPP