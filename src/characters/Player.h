#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "../inventory/Inventory.h"
#include "../items/Weapon.h"

class Player : public Character {
private:
    Inventory* inventory;
    Weapon* equippedWeapon; // currently equipped weapon (if any)

public:
    Player(const string &name, int health);
    ~Player() override;
    
    void attack(Character* target) override;
    void addItem(Item* item);
    void showInventory();
    void equipWeapon();
    void showEquippedWeapon();
};

#endif
