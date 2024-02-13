//
// Created by özgür yalçın on 8.02.2024.
//

#ifndef THEGAMEWITHNINJAS_USERMODEL_H
#define THEGAMEWITHNINJAS_USERMODEL_H

#include "common.h"

struct UserModel
{
    UserModel(const std::string& inName, CharType inCharType, int inLevel): name{inName}, charType{toString(inCharType)}, level(inLevel) {};
    std::string name;
    std::string charType;
    int level;
};


#endif //THEGAMEWITHNINJAS_USERMODEL_H
