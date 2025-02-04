#include "Inventory.h"
#include "../items/Weapon.h"
#include <iostream>
using namespace std;

InventoryNode::InventoryNode(Item* i) : item(i), next(nullptr) {}

Inventory::Inventory() : head(nullptr) {}

Inventory::~Inventory() {
    InventoryNode* current = head;

    while(current != nullptr) {
        InventoryNode* temp = current;
        current = current->next;
        delete temp->item; // free the item
        delete temp;
    }
}

void Inventory::addItem(Item* item) {
    InventoryNode* newNode = new InventoryNode(item);
    newNode->next = head;
    head = newNode;
    cout << "Added " << item->name << " to your inventory!\n";
}

Item* Inventory::removeItemAtIndex(int index) {
    if(index <= 0) return nullptr;

    InventoryNode* current = head;
    InventoryNode* previous = nullptr;
    int count = 1;

    while(current && count < index) {
        previous = current;
        current = current->next;
        count++;
    }

    if(!current) return nullptr;

    if(previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    Item* removedItem = current->item;
    delete current;
    return removedItem;
}

void Inventory::displayItems() {
    if(!head) {
        cout << "Your inventory is empty.\n";
        return;
    }

    cout << "\n-- Inventory --\n";

    InventoryNode* current = head;
    int index = 1;

    while(current != nullptr) {
        cout << index << ". " << current->item->name << " (Value: " << current->item->value << ")";
        Weapon* w = dynamic_cast<Weapon*>(current->item);
        
        if(w) { cout << " [Damage Bonus: " << w->damageBonus << "]"; }
        
        cout << "\n";
        current = current->next;
        index++;
    }

    cout << "---------------\n";
}

vector<Item*> Inventory::getItems() {
    vector<Item*> items;
    InventoryNode* current = head;

    while(current) {
        items.push_back(current->item);
        current = current->next;
    }
    
    return items;
}
