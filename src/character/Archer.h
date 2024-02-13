//
// Created by özgür yalçın on 6.02.2024.
//

#ifndef THEGAMEWITHNINJAS_ARCHER_H
#define THEGAMEWITHNINJAS_ARCHER_H

#include "Character.h"

class Archer : public Character {
public:
    Archer(const std::string&  name, int level) : Character(name, level){}
    void attack() const override;
    // Destructor
    ~Archer() override {}

};


#endif //THEGAMEWITHNINJAS_ARCHER_H
