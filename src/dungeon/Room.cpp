#include "Room.h"
#include <iostream>
using namespace std;

Room::Room(int id, const string &desc, Character* enemy, Item* item) : id(id), description(desc), enemy(enemy), roomItem(item) {}

Room::~Room() {
    if(enemy) { delete enemy; }
    if(roomItem) { delete roomItem; }
}

int Room::getId() const { return id; }

string Room::getDescription() const { return description; }
bool Room::hasEnemy() const { return enemy != nullptr && enemy->isAlive(); }
bool Room::hasItem() const { return roomItem != nullptr; }

Character* Room::getEnemy() { return enemy; }

Item* Room::takeItem() {
    if(!roomItem) return nullptr;

    Item* temp = roomItem;
    roomItem = nullptr;
    
    return temp;
}

string Room::getItemName() const { return roomItem ? roomItem->name : ""; }
