#include "Database.hpp"

Database::Database(const char *path)
:   _path(path), _db(_path, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{
    _db.exec("DROP TABLE IF EXISTS user");

    // Begin transaction
    SQLite::Transaction transaction(_db);
    _db.exec("CREATE TABLE user (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)");
    int nb;
    nb = _db.exec("INSERT INTO user (username, password) VALUES (\"idan\", \"1234\")");
    // std::cout << "INSERT INTO test VALUES (1, \"idan\")\", \"1234\", returned " << nb << std::endl;
    nb = _db.exec("INSERT INTO user (username, password) VALUES (\"lirans59\", \"5989\")");
    // std::cout << "INSERT INTO test VALUES (2, \"lirans59\")\", \"5989\", returned " << nb << std::endl;

    // Commit transaction
    transaction.commit();
}

Database::~Database()
{
}

void Database::add(std::string& username, std::string& password)
{
    SQLite::Transaction transaction(_db);
    
    std::string cmd = "INSERT INTO user (username, password) VALUES(\"" +
    username + "\", \"" + password + "\")";

    int nb = _db.exec(cmd);
    std::cout << cmd << ", returned " << nb << std::endl;

    // Commit transaction
    transaction.commit();
}
void Database::remove(std::string& username)
{
    SQLite::Statement query(_db, "DELETE FROM user WHERE username = ?");
    query.bind(1, username);
    query.executeStep();
}
bool Database::valid(std::string& username, std::string& password)
{
    SQLite::Statement query(_db, "SELECT * FROM user WHERE username = ? AND password = ?");
    query.bind(1, username.c_str());
    query.bind(2, password.c_str());
    if(query.executeStep())
    {
        return true;
    }
    return false;
}