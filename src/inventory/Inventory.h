#ifndef INVENTORY_H
#define INVENTORY_H

#include "../items/Item.h"
#include <vector>
using namespace std;

struct InventoryNode {
    Item* item;
    InventoryNode* next;
    InventoryNode(Item* i);
};

class Inventory {
private:
    InventoryNode* head;
public:
    Inventory();
    ~Inventory();
    void addItem(Item* item);
    Item* removeItemAtIndex(int index);
    void displayItems();
    vector<Item*> getItems();
};

#endif
