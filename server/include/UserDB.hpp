#ifndef USERDB_HPP
#define USERDB_HPP

#pragma once

#define FILE_NAME "users.txt"

#include <iostream>
#include <fstream>

class UserDB
{
public:
    UserDB();
    ~UserDB();
    void add(std::string& user);
    void remove(std::string& username);
    bool valid(std::string& username, std::string& password);

private:
    std::ofstream   _ofile;
    std::ifstream   _ifile;
};

#endif // USERDB_HPP