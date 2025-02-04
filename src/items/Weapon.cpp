#include "Weapon.h"

Weapon::Weapon(const string &name, int value, int bonus) : Item(name, value), damageBonus(bonus) {}

void Weapon::use() {
    std::cout << "You swing the " << name << ", adding +" << damageBonus << " damage!\n";
}
