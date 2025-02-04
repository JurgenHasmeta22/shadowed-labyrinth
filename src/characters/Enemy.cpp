#include "Enemy.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Enemy::Enemy(const string &name, int health) : Character(name, health) {}

void Enemy::attack(Character* target) {
    int damage = (rand() % 11) + 5; // damage between 5 and 15
    cout << name << " attacks " << target->getName() << " for " << damage << " damage!\n";
    target->takeDamage(damage);
}
