#ifndef ROOM_H
#define ROOM_H

#include "../characters/Character.h"
#include "../items/Item.h"
#include <string>
using namespace std;

class Room {
private:
    int id;
    string description;
    Character* enemy;  // enemy present in the room (if any)
    Item* roomItem;    // item present in the room (if any)
    
public:
    Room(int id, const string &desc, Character* enemy = nullptr, Item* item = nullptr);
    ~Room();
    int getId() const;
    string getDescription() const;
    bool hasEnemy() const;
    bool hasItem() const;
    Character* getEnemy();
    Item* takeItem();
    string getItemName() const;
};

#endif
