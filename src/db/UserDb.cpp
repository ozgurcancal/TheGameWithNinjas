//
// Created by özgür yalçın on 27.01.2024.
//


#include "UserDb.h"
#include <iostream>

UserDB::UserDB() {
    setupDB();
}


UserDB::~UserDB()
{
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

int UserDB::setupDB()
{
    const std::lock_guard<std::mutex> lock(mtx);

    // SQL statement to create a 'users' tablew
    const char* createTableSql = "CREATE TABLE IF NOT EXISTS users ("
                                 //  "id INTEGER PRIMARY KEY, "
                                 "NAME TEXT PRIMARY KEY, "
                                 "CHARTYPE TEXT NOT NULL,"
                                 "LEVEL INTEGER)";

    int rv = sqlite3_open(USER_DB_PATH, &db);
    if (rv != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    // Execute the SQL statement to create the table
    rv = sqlite3_exec(db, createTableSql, 0, 0, 0);
    if (rv != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    return SQLITE_OK;
}

int UserDB::getUser(const std::string& userName, UserModel& outUser)
{
    // Prepare a SQL query
    const char* getQuery = "SELECT * FROM users WHERE NAME = ?";

    sqlite3_stmt *pStmt;
    int rv = sqlite3_prepare_v2(db, getQuery, -1, &pStmt, 0);
    if (rv != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }
    sqlite3_bind_text(pStmt, 1, userName.c_str(), -1, SQLITE_STATIC);
    rv = sqlite3_step(pStmt);

    if (rv != SQLITE_ROW){
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }
    outUser.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 0)));
    outUser.charType = std::string(reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 1)));
    outUser.level = sqlite3_column_int(pStmt, 3);

    return SQLITE_OK;
}

int UserDB::addUser(const UserModel& toAdd)
{
    std::lock_guard<std::mutex> lock(mtx);
    // Prepare the SQL statement
     const char* insertQuery = "INSERT OR REPLACE INTO users(NAME, CHARTYPE, LEVEL)"
                                        "VALUES(?1, ?2, ?3)";
    sqlite3_stmt *pStmt;

    int rv = sqlite3_prepare_v2(db, insertQuery, -1, &pStmt, 0);
    if (rv != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }
    //SQLITE_STATIC means SQLite does not need to copy username
    rv = sqlite3_bind_text(pStmt, 1, toAdd.name.c_str(), toAdd.name.length(), SQLITE_STATIC);
    if (rv != SQLITE_OK) {
        std::cerr << "SQL bind_text error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }

    rv = sqlite3_bind_text(pStmt, 2, toAdd.charType.c_str(), toAdd.charType.length(), SQLITE_STATIC);
    if (rv != SQLITE_OK) {
        std::cerr << "SQL bind_text error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }

    rv = sqlite3_bind_int(pStmt, 3, toAdd.level);
    if (rv != SQLITE_OK) {
        std::cerr << "SQL bind_int error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }

    rv = sqlite3_step(pStmt);
    if (rv != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }

    sqlite3_finalize(pStmt);

    return SQLITE_OK;
}

int UserDB::updateUser(const std::string& user, const std::string& charType, const int level)
{
    std::lock_guard<std::mutex> lock(mtx);

    const char* insertCmd = "UPDATE users SET CHARTYPE = ?, LEVEL = ? WHERE NAME = ?" ;
    sqlite3_stmt *pStmt;

    int rv = sqlite3_prepare_v2(db, insertCmd, -1, &pStmt, 0);
    if (rv != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return rv;
    }

    sqlite3_bind_text(pStmt, 1, charType.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(pStmt, 2, level);
    sqlite3_bind_text(pStmt, 3, user.c_str(), -1, SQLITE_STATIC);

    // Execute the prepared statement and fetch data
    rv = sqlite3_step(pStmt);

    if (rv != SQLITE_DONE) {
        std::cerr << "Update failed: " << sqlite3_errmsg(db);
        return rv;
    }

    // Finalize the statement
    sqlite3_finalize(pStmt);

    return SQLITE_OK;
}

