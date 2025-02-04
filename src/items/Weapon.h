#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    int damageBonus;
    Weapon(const string &name, int value, int bonus);
    void use() override;
};

#endif
