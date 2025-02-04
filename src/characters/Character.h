#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health;

public:
    Character(const string &name, int health);

    virtual ~Character();
    virtual void attack(Character* target) = 0;
    
    bool isAlive() const;
    string getName() const;
    int getHealth() const;
    void takeDamage(int damage);
};

#endif
