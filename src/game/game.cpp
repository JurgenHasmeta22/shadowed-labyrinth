#include "Game.h"
#include <iostream>
#include <cstdlib>
#include "../characters/Enemy.h"
#include "../characters/Troll.h"
#include "../items/Item.h"
#include "../items/Weapon.h"
using namespace std;

Game::Game() {
    // Create the player.
    player = new Player("Hero", 100);

    // Create the dungeon and add several rooms.
    dungeon = new Dungeon();

    // Room 1: an empty corridor with a treasure.
    dungeon->addRoom(new Room(1, "A dimly lit corridor. You see something shimmering on the floor.", nullptr, new Item("Silver Coin", 10)));

    // Room 2: a room with a Goblin.
    dungeon->addRoom(new Room(2, "A musty room with cobwebs. A sneaky Goblin lurks here.", new Enemy("Goblin", 40), nullptr));

    // Room 3: a room with a Troll.
    dungeon->addRoom(new Room(3, "A large hall with echoing footsteps. A fearsome Troll stands before you.", new Troll("Troll", 60), nullptr));

    // Room 4: a treasure room with a weapon.
    dungeon->addRoom(new Room(4, "A glittering chamber filled with treasures. A mighty sword rests on a pedestal.", nullptr, new Weapon("Excalibur", 150, 10)));

    // Set current room to the start of the dungeon.
    currentRoom = dungeon->getStart();
}

Game::~Game() {
    delete player;
    delete dungeon;
}

void Game::describeCurrentRoom() {
    cout << "\n=== Room " << currentRoom->getId() << " ===\n";
    cout << currentRoom->getDescription() << "\n";
    if(currentRoom->hasEnemy()) {
        cout << "An enemy is here: " << currentRoom->getEnemy()->getName() << " (Health: " << currentRoom->getEnemy()->getHealth() << ")\n";
    }
    if(currentRoom->hasItem()) {
        cout << "There is an item on the ground: " << currentRoom->getItemName() << "\n";
    }
}

void Game::displayMenu() {
    cout << "\nChoose an action:\n";
    cout << "1. Attack enemy\n";
    cout << "2. Pick up item\n";
    cout << "3. Move to next room\n";
    cout << "4. Check inventory\n";
    cout << "5. Do nothing\n";
    cout << "6. Equip weapon\n";
    cout << "7. Check equipped weapon\n";
    cout << "8. Look around\n";
    cout << "9. Quit game\n";
    cout << "Enter your choice: ";
}

void Game::run() {
    cout << "Welcome to the Dungeon Crawler!\n";
    bool gameOver = false;

    while(!gameOver && player->isAlive()) {
        cout << "\n---------------------------\n";
        cout << "You are in Room " << currentRoom->getId() << ".\n";
        cout << currentRoom->getDescription() << "\n";

        if(currentRoom->hasEnemy()) {
            cout << "An enemy (" << currentRoom->getEnemy()->getName() << ") is here!\n";
        }

        if(currentRoom->hasItem()) {
            cout << "There is an item lying on the floor: " << currentRoom->getItemName() << "\n";
        }

        cout << "---------------------------\n";

        displayMenu();

        int choice;
        cin >> choice;
        cout << "\n";

        switch(choice) {
            case 1: {
                if(currentRoom->hasEnemy()) {
                    while(currentRoom->hasEnemy() && player->isAlive()) {
                        // Player attacks enemy.
                        player->attack(currentRoom->getEnemy());

                        if(!currentRoom->getEnemy()->isAlive()) {
                            cout << "You defeated the " << currentRoom->getEnemy()->getName() << "!\n";
                            break;
                        }

                        // Enemy attacks back.
                        currentRoom->getEnemy()->attack(player);

                        if(!player->isAlive()) {
                            cout << "You have been defeated in battle...\n";
                            gameOver = true;
                            break;
                        }
                    }
                } else {
                    cout << "There is no enemy here to attack!\n";
                }

                break;
            }
            case 2: {
                if(currentRoom->hasItem()) {
                    Item* item = currentRoom->takeItem();

                    if(item) {
                        cout << "You pick up the " << item->name << ".\n";
                        player->addItem(item);
                    }
                } else {
                    cout << "There is no item here.\n";
                }

                break;
            }
            case 3: {
                Room* nextRoom = dungeon->getNextRoom(currentRoom->getId());

                if(nextRoom) {
                    currentRoom = nextRoom;
                    cout << "You move to Room " << currentRoom->getId() << ".\n";
                } else {
                    cout << "There are no more rooms. You have reached the end of the dungeon!\n";
                    gameOver = true;
                }

                break;
            }
            case 4: {
                player->showInventory();
                break;
            }
            case 5: {
                cout << "You wait and gather your thoughts...\n";

                if(currentRoom->hasEnemy()) {
                    cout << "The enemy seizes the moment!\n";
                    currentRoom->getEnemy()->attack(player);
                }
                
                break;
            }
            case 6: {
                player->equipWeapon();
                break;
            }
            case 7: {
                player->showEquippedWeapon();
                break;
            }
            case 8: {
                describeCurrentRoom();
                break;
            }
            case 9: {
                cout << "Quitting the game. Farewell, adventurer!\n";
                gameOver = true;
                break;
            }
            default:
                cout << "Invalid choice! You hesitate and lose your chance to act.\n";
                break;
        }

        if(!player->isAlive()) {
            cout << "\nGame Over. You have perished in the dungeon.\n";
            gameOver = true;
        }
    }

    if(player->isAlive()) {
        cout << "\nCongratulations! You survived the dungeon crawl.\n";
    }
}
