#include "UserDB.hpp"

UserDB::UserDB()
{
}

UserDB::~UserDB()
{
}

void UserDB::add(std::string& user)
{
    _ofile.open(FILE_NAME, std::ios::app);
    _ofile << user << std::endl;
}
void UserDB::remove(std::string& username)
{
    std::string line;
    _ofile.open("temp.txt", std::ios::app);
    _ifile.open(FILE_NAME);

    while(std::getline(_ifile, line))
    {
        if( line.find(username) )
        {
            _ofile << line << std::endl;
            break;
        }
    }
    std::rename("temp.txt", FILE_NAME);
    _ifile.close();
    _ofile.close();
}
bool UserDB::valid(std::string& username, std::string& password)
{
    std::string line;
    _ifile.open(FILE_NAME);

    while(std::getline(_ifile, line))
    {
        if( line.find(username) ){
            if( line.find(password) ){
                return true;
            }
            break;
        }
    }
    return false;
}