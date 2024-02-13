//
// Created by özgür yalçın on 6.02.2024.
//

#include "Character.h"

Character::Character(const std::string&  name, int level) : m_name(name), m_level(level) {};

std::string Character::getName() const {
    return m_name;
}

int Character::getLevel() const {
    return m_level;
}

int Character::getHealth() const {
    return m_health;
}

void Character::setName(const std::string& newName) { m_name = newName; }
void Character::setLevel(int newLevel) { m_level = newLevel; }
void Character::setHealth(int newHealth) { m_health = newHealth; }

void Character::displayInfo() const {
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Level: " << m_level << std::endl;
    std::cout << "Health: " << m_health << std::endl;
}


