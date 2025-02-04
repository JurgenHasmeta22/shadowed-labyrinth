#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    Enemy(const string &name, int health);
    void attack(Character* target) override;
};

#endif
