#include "Dungeon.h"
#include <iostream>
using namespace std;

Dungeon::RoomNode::RoomNode(Room* r) : room(r), next(nullptr) {}

Dungeon::Dungeon() : head(nullptr) {}

Dungeon::~Dungeon() {
    RoomNode* current = head;
    
    while(current) {
        RoomNode* temp = current;
        current = current->next;
        delete temp->room;
        delete temp;
    }
}

void Dungeon::addRoom(Room* room) {
    RoomNode* newNode = new RoomNode(room);

    if(!head) {
        head = newNode;
    } else {
        RoomNode* current = head;
        while(current->next) { current = current->next; }
        current->next = newNode;
    }
}

Room* Dungeon::getStart() {
    return head ? head->room : nullptr;
}

Room* Dungeon::getNextRoom(int currentId) {
    RoomNode* current = head;

    while(current) {
        if(current->room->getId() == currentId && current->next) {
            return current->next->room;
        }

        current = current->next;
    }

    return nullptr;
}
