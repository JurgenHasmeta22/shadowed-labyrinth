#ifndef GAME_H
#define GAME_H

#include "../characters/Player.h"
#include "../dungeon/Dungeon.h"
#include "../dungeon/Room.h"

class Game {
private:
    Player* player;
    Dungeon* dungeon;
    Room* currentRoom;

public:
    Game();
    ~Game();
    
    void describeCurrentRoom();
    void displayMenu();
    void run();
};

#endif
