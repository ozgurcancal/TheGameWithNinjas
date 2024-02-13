//
// Created by özgür yalçın on 27.01.2024.
//

#ifndef THEGAMEWITHNINJAS_USERDB_H
#define THEGAMEWITHNINJAS_USERDB_H

#include "UserModel.h"

#include <string>
#include <sqlite3.h>
#include <mutex>


class UserDB {
public:
    static UserDB& getInstance(){
        static UserDB instance;
        return instance;
    }

    UserDB(const UserDB&) = delete;
    UserDB& operator=(const UserDB&) = delete;


    int addUser(const UserModel& toAdd);
    int updateUser(const std::string& user, const std::string& charType, const int level);
    int getUser(const std::string& user, UserModel& outUser);

private:
    static constexpr const char* USER_DB_PATH = "/Users/ozguryalcin/Documents/projects/TheGameWithNinjas/sqlite/userDb.sqlite";

    UserDB();
    ~UserDB();

    int setupDB();

    sqlite3* db = nullptr;
    std::mutex mtx;

};


#endif //THEGAMEWITHNINJAS_USERDB_H
