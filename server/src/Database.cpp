#include "Database.hpp"

Database::Database(const char *path)
:   _path(path), _db(_path, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)//, _query(_db, "SELECT * FROM test WHERE weight > :min_weight")
{
    _db.exec("DROP TABLE IF EXISTS user");

    // Begin transaction
    SQLite::Transaction transaction(_db);

    _db.exec("CREATE TABLE user (id INTEGER PRIMARY KEY, username TEXT, password TEXT)");

    int nb = _db.exec("INSERT INTO user VALUES (0, \"idan\", \"1234\")");
    std::cout << "INSERT INTO test VALUES (0, \"idan\")\", \"1234\", returned " << nb << std::endl;

    // Commit transaction
    transaction.commit();
}

Database::~Database()
{
}

void Database::add(std::string& username, std::string& password)
{
}
void Database::remove(std::string& username)
{
}
bool Database::valid(std::string& username, std::string& password)
{
    SQLite::Statement   query(_db, "SELECT * FROM user WHERE username = ? AND password = ?");
    
    username.pop_back();
    password.pop_back();
    query.bind(1, username.c_str());
    query.bind(2, password.c_str());
    // query.bind(2, password.c_str());
    if(query.executeStep())
    {
        return true;
    }
    return false;
}