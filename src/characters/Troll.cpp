#include "Troll.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Troll::Troll(const string &name, int health) : Enemy(name, health) {}

void Troll::attack(Character* target) {
    int damage = (rand() % 11) + 10; // damage between 10 and 20
    cout << name << " swings a massive club at " << target->getName() << " for " << damage << " damage!\n";
    target->takeDamage(damage);
}
