#ifndef TROLL_H
#define TROLL_H

#include "Enemy.h"

class Troll : public Enemy {
public:
    Troll(const string &name, int health);
    void attack(Character* target) override;
};

#endif
