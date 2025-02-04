#include "Character.h"
#include <iostream>
using namespace std;

Character::Character(const string &name, int health) : name(name), health(health) {}
Character::~Character() {}

bool Character::isAlive() const { return health > 0; }
string Character::getName() const { return name; }
int Character::getHealth() const { return health; }

void Character::takeDamage(int damage) {
    health -= damage;

    if(health < 0) { health = 0; }
    
    cout << name << " takes " << damage << " damage! (Health: " << health << ")\n";
}
