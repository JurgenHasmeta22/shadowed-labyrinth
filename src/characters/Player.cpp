#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Player::Player(const string &name, int health) : Character(name, health), equippedWeapon(nullptr) {
    inventory = new Inventory();
}

Player::~Player() {
    delete inventory;
}

void Player::attack(Character* target) {
    int baseDamage = (rand() % 11) + 10; // damage between 10 and 20
    int bonus = (equippedWeapon != nullptr) ? equippedWeapon->damageBonus : 0;
    int totalDamage = baseDamage + bonus;

    cout << name << " attacks " << target->getName() << " for " << totalDamage << " damage";
    
    if(bonus > 0) { cout << " (Base: " << baseDamage << " + Bonus: " << bonus << ")"; }
    
    cout << "!\n";
    target->takeDamage(totalDamage);
}

void Player::addItem(Item* item) {
    inventory->addItem(item);
}

void Player::showInventory() {
    inventory->displayItems();
}

void Player::equipWeapon() {
    cout << "\n-- Equip Weapon --\n";
    inventory->displayItems();
    cout << "Enter the index of the weapon to equip (or 0 to cancel): ";
    int index;
    cin >> index;

    if(index == 0) {
        cout << "Equip cancelled.\n";
        return;
    }

    Item* selected = inventory->removeItemAtIndex(index);

    if(selected == nullptr) {
        cout << "Invalid selection!\n";
        return;
    }

    Weapon* weapon = dynamic_cast<Weapon*>(selected);

    if(weapon == nullptr) {
        cout << "The selected item is not a weapon. Returning it to inventory.\n";
        inventory->addItem(selected);
        return;
    }

    if(equippedWeapon != nullptr) {
        cout << "Unequipping current weapon (" << equippedWeapon->name << ") and returning it to inventory.\n";
        inventory->addItem(equippedWeapon);
    }
    
    equippedWeapon = weapon;
    cout << "You have equipped " << equippedWeapon->name << " (Damage Bonus: " << equippedWeapon->damageBonus << ").\n";
}

void Player::showEquippedWeapon() {
    if(equippedWeapon)
        cout << "Currently equipped weapon: " << equippedWeapon->name << " (Damage Bonus: " << equippedWeapon->damageBonus << ")\n";
    else
        cout << "No weapon equipped.\n";
}
