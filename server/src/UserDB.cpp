#include "UserDB.hpp"

UserDB::UserDB(const char *name)
:   _name(name)
{
}

UserDB::~UserDB()
{
}

void UserDB::add(std::string& user)
{
    _ofile.open(_name, std::ios::app);
    _ofile << user << std::endl;
}
void UserDB::remove(std::string& username)
{
    std::string line;
    _ofile.open("temp.txt", std::ios::app);
    _ifile.open(_name);

    while(std::getline(_ifile, line))
    {
        if( line.find(username) )
        {
            _ofile << line << std::endl;
            break;
        }
    }
    std::rename("temp.txt", _name);
    _ifile.close();
    _ofile.close();
}
bool UserDB::valid(std::string& username, std::string& password)
{
    std::string line;
    _ifile.open(_name);
    _ifile.clear();
    _ifile.seekg (0, std::ios::beg);

    username.pop_back();
    password.pop_back();
    while(std::getline(_ifile, line))
    {
        if( line.find(username + " ") != std::string::npos){
            if( line.find(password, username.size() + 1) != std::string::npos){
                return true;
            }
            break;
        }
    }
    return false;
}