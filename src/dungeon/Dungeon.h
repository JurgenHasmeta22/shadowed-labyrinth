#ifndef DUNGEON_H
#define DUNGEON_H

#include "Room.h"

class Dungeon {
private:
    struct RoomNode {
        Room* room;
        RoomNode* next;
        RoomNode(Room* r);
    };

    RoomNode* head;
    
public:
    Dungeon();
    ~Dungeon();
    void addRoom(Room* room);
    Room* getStart();
    Room* getNextRoom(int currentId);
};

#endif
