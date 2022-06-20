#include "Database.hpp"

Database::Database(const char *file)
:   _file(file), _db(_file)//, _query(_db, "SELECT * FROM test WHERE weight > :min_weight")
{
}

Database::~Database()
{
}

void Database::add(std::string& user)
{
}
void Database::remove(std::string& username)
{
}
bool Database::valid(std::string& username, std::string& password)
{
    return true;
}