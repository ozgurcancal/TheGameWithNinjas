//
// Created by özgür yalçın on 6.02.2024.
//

#ifndef THEGAMEWITHNINJAS_CHARACTER_H
#define THEGAMEWITHNINJAS_CHARACTER_H


#include <iostream>
#include <string>

class Character {
protected:

    Character(const std::string&  name, int level);

public:
    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~Character() = default;

    // Getters and setters
    std::string getName() const;
    int getLevel() const;
    int getHealth() const;

    void setName(const std::string& newName);
    void setLevel(int newLevel);
    void setHealth(int newHealth);

    virtual void attack() const = 0;

    virtual void displayInfo() const;

private:

    std::string m_name;
    int m_level = 0;
    int m_health = 100;




};


#endif //THEGAMEWITHNINJAS_CHARACTER_H
