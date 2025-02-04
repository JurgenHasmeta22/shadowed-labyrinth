#include "Item.h"

Item::Item(const string &name, int value) : name(name), value(value) {}

Item::~Item() {}

void Item::use() {
    std::cout << "You use the " << name << ".\n";
}
