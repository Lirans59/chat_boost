#include "Database.hpp"

Database::Database(const char *path)
:   _path(path), _db(_path, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE),
    _query_login(_db, "SELECT * FROM user WHERE username = ? AND password = ?"),
    _query_remove_user(_db, "DELETE FROM user WHERE username = ?"),
    _count(2)
{
    _db.exec("DROP TABLE IF EXISTS user");

    // Begin transaction
    SQLite::Transaction transaction(_db);

    _db.exec("CREATE TABLE user (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)");
    /*  This is a security issue. The usernames and passwords should not be in the elf (as all
        string literals) */
    int nb;
    nb = _db.exec("INSERT INTO user VALUES (1, \"idan\", \"1234\")");
    std::cout << "INSERT INTO test VALUES (1, \"idan\")\", \"1234\", returned " << nb << std::endl;
    nb = _db.exec("INSERT INTO user VALUES (2, \"lirans59\", \"5989\")");
    std::cout << "INSERT INTO test VALUES (2, \"lirans59\")\", \"5989\", returned " << nb << std::endl;

    // Commit transaction
    transaction.commit();
}

Database::~Database()
{
}

void Database::add(std::string& username, std::string& password)
{
    SQLite::Transaction transaction(_db);
    
    std::string cmd = "INSERT INTO user VALUES (" + std::to_string(++_count) + ", " +
    "\"" + username + "\", \"" + password + "\")";
    int nb = _db.exec(cmd);
    std::cout << cmd << ", returned " << nb << std::endl;

    // Commit transaction
    transaction.commit();
}
void Database::remove(std::string& username)
{
    _query_remove_user.reset();
    _query_remove_user.bind(1, username);
    _query_remove_user.executeStep();
}
bool Database::valid(std::string& username, std::string& password)
{
    _query_login.reset();
    _query_login.bind(1, username.c_str());
    _query_login.bind(2, password.c_str());
    if(_query_login.executeStep())
    {
        return true;
    }
    return false;
}