#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// -----------------------------------------------------------------
// Item classes
// -----------------------------------------------------------------

// Base Item class: represents any collectible object.
class Item
{
public:
    string name;
    int value;

    Item(const string &name, int value)
        : name(name), value(value) {}

    virtual ~Item() {}

    virtual void use()
    {
        cout << "You use the " << name << ".\n";
    }
};

// Derived Weapon class: increases attack damage.
class Weapon : public Item
{
public:
    int damageBonus;

    Weapon(const string &name, int value, int bonus)
        : Item(name, value), damageBonus(bonus) {}

    void use() override
    {
        cout << "You swing the " << name << ", adding +" << damageBonus << " damage!\n";
    }
};

// -----------------------------------------------------------------
// Inventory implemented as a linked list
// -----------------------------------------------------------------

// Node for the linked list of inventory items.
struct InventoryNode
{
    Item *item;
    InventoryNode *next;

    InventoryNode(Item *i)
        : item(i), next(nullptr) {}
};

// Inventory class: holds items in a linked list.
class Inventory
{
private:
    InventoryNode *head;

public:
    Inventory() : head(nullptr) {}

    ~Inventory()
    {
        InventoryNode *current = head;
        while (current != nullptr)
        {
            InventoryNode *temp = current;
            current = current->next;
            delete temp->item; // free the item
            delete temp;       // free the node
        }
    }

    // Add an item at the beginning.
    void addItem(Item *item)
    {
        InventoryNode *newNode = new InventoryNode(item);
        newNode->next = head;
        head = newNode;
        cout << "Added " << item->name << " to your inventory!\n";
    }

    // Remove and return an item by its 1-based index.
    // Returns nullptr if index is invalid.
    Item *removeItemAtIndex(int index)
    {
        if (index <= 0)
            return nullptr;

        InventoryNode *current = head;
        InventoryNode *previous = nullptr;
        int count = 1;

        while (current && count < index)
        {
            previous = current;
            current = current->next;
            count++;
        }

        if (!current)
            return nullptr; // index out of bounds
        // Remove the node from the list.

        if (previous == nullptr)
        {
            head = current->next;
        }

        else
        {
            previous->next = current->next;
        }

        Item *removedItem = current->item;

        delete current;
        return removedItem;
    }

    // Display all items in the inventory with an index.
    void displayItems()
    {
        if (!head)
        {
            cout << "Your inventory is empty.\n";
            return;
        }

        cout << "\n-- Inventory --\n";
        InventoryNode *current = head;
        int index = 1;

        while (current != nullptr)
        {
            cout << index << ". " << current->item->name
                 << " (Value: " << current->item->value << ")";
            // If the item is a weapon, display its bonus.

            Weapon *w = dynamic_cast<Weapon *>(current->item);

            if (w)
            {
                cout << " [Damage Bonus: " << w->damageBonus << "]";
            }

            cout << "\n";
            current = current->next;
            index++;
        }

        cout << "---------------\n";
    }

    // Return a vector of all items (for inspection if needed).
    vector<Item *> getItems()
    {
        vector<Item *> items;
        InventoryNode *current = head;

        while (current)
        {
            items.push_back(current->item);
            current = current->next;
        }

        return items;
    }
};

// -----------------------------------------------------------------
// Character classes
// -----------------------------------------------------------------

// Abstract base class for any character in the game.
class Character
{
protected:
    string name;
    int health;

public:
    Character(const string &name, int health)
        : name(name), health(health) {}

    virtual ~Character() {}

    virtual void attack(Character *target) = 0;

    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getHealth() const { return health; }

    void takeDamage(int damage)
    {
        health -= damage;

        if (health < 0)
            health = 0;

        cout << name << " takes " << damage << " damage! (Health: " << health << ")\n";
    }
};

// Player class: controlled by the user.
class Player : public Character
{
private:
    Inventory *inventory;
    Weapon *equippedWeapon; // pointer to currently equipped weapon (if any)

public:
    Player(const string &name, int health)
        : Character(name, health), equippedWeapon(nullptr)
    {
        inventory = new Inventory();
    }

    ~Player() override
    {
        delete inventory;
    }

    // Attack: uses a weapon bonus if equipped.
    void attack(Character *target) override
    {
        int baseDamage = (rand() % 11) + 10; // base damage between 10 and 20
        int bonus = (equippedWeapon != nullptr) ? equippedWeapon->damageBonus : 0;
        int totalDamage = baseDamage + bonus;

        cout << name << " attacks " << target->getName() << " for "
             << totalDamage << " damage";

        if (bonus > 0)
            cout << " (Base: " << baseDamage << " + Bonus: " << bonus << ")";
        cout << "!\n";

        target->takeDamage(totalDamage);
    }

    void addItem(Item *item)
    {
        inventory->addItem(item);
    }

    void showInventory()
    {
        inventory->displayItems();
    }

    // Equip a weapon from inventory.
    // Displays the inventory and prompts the user to choose a weapon.
    void equipWeapon()
    {
        cout << "\n-- Equip Weapon --\n";
        inventory->displayItems();
        cout << "Enter the index of the weapon to equip (or 0 to cancel): ";

        int index;
        cin >> index;

        if (index == 0)
        {
            cout << "Equip cancelled.\n";
            return;
        }

        Item *selected = inventory->removeItemAtIndex(index);

        if (selected == nullptr)
        {
            cout << "Invalid selection!\n";
            retu
                rn;
        }
        Weapon *weapon = dynamic_cast<Weapon *>(selected);

        if (weapon == nullptr)
        {
            cout << "The selected item is not a weapon. Returning it to inventory.\n";
            inventory->addItem(selected);
            return;
        }

        // If a weapon is already equipped, return it to the inventory.
        if (equippedWeapon != nullptr)
        {
            cout << "Unequipping current weapon (" << equippedWeapon->name << ") and returning it to inventory.\n";
            inventory->addItem(equippedWeapon);
        }

        equippedWeapon = weapon;
        cout << "You have equipped " << equippedWeapon->name << " (Damage Bonus: " << equippedWeapon->damageBonus << ").\n";
    }

    // Optionally, allow the player to view the currently equipped weapon.
    void showEquippedWeapon()
    {
        if (equippedWeapon)
            cout << "Currently equipped weapon: " << equippedWeapon->name
                 << " (Damage Bonus: " << equippedWeapon->damageBonus << ")\n";
        else
            cout << "No weapon equipped.\n";
    }
};

// Enemy classes

// A generic enemy type.
class Enemy : public Character
{
public:
    Enemy(const string &name, int health)
        : Character(name, health) {}

    // Default enemy attack: damage between 5 and 15.
    void attack(Character *target) override
    {
        int damage = (rand() % 11) + 5;
        cout << name << " attacks " << target->getName()
             << " for " << damage << " damage!\n";

        target->takeDamage(damage);
    }
};

// A tougher enemy: Troll.
class Troll : public Enemy
{
public:
    Troll(const string &name, int health)
        : Enemy(name, health) {}

    // Trolls hit harder with damage between 10 and 20.
    void attack(Character *target) override
    {
        int damage = (rand() % 11) + 10;
        cout << name << " swings a massive club at " << target->getName()
             << " for " << damage << " damage!\n";

        target->takeDamage(damage);
    }
};

// -----------------------------------------------------------------
// Room and Dungeon classes (implemented as a linked list of rooms)
// -----------------------------------------------------------------

// Forward declaration of Room.
class Room;

// Node for the dungeon's linked list of rooms.
struct RoomNode
{
    Room *room;
    RoomNode *next;

    RoomNode(Room *r) : room(r), next(nullptr) {}
};

// Room class: represents a room in the dungeon.
class Room
{
private:
    int id;
    string description;

    // Each room may have an enemy and/or an item (treasure or weapon)
    Character *enemy; // pointer to an enemy (if present)
    Item *roomItem;   // pointer to an item (if present)
public:
    Room(int id, const string &desc, Character *enemy = nullptr, Item *item = nullptr)
        : id(id), description(desc), enemy(enemy), roomItem(item) {}

    ~Room()
    {
        if (enemy)
            delete enemy;

        if (roomItem)
            delete roomItem;
    }

    int getId() const { return id; }
    string getDescription() const { return description; }

    bool hasEnemy() const { return enemy != nullptr && enemy->isAlive(); }
    bool hasItem() const { return roomItem != nullptr; }

    // Get pointer to the enemy.
    Character *getEnemy() { return enemy; }

    // Remove the item from the room and return it.
    // This method is called when the player picks up the item.
    Item *takeItem()
    {
        if (!roomItem)
            return nullptr;

        Item *temp = roomItem;
        roomItem = nullptr;
        return temp;
    }

    // Return the name of the item without removing it.
    string getItemName() const
    {
        return roomItem ? roomItem->name : "";
    }
};

// Dungeon class: holds a linked list of rooms.
class Dungeon
{
private:
    RoomNode *head;

public:
    Dungeon() : head(nullptr) {}

    ~Dungeon()
    {
        RoomNode *current = head;

        while (current)
        {
            RoomNode *temp = current;
            current = current->next;
            delete temp->room;
            delete temp;
        }
    }

    // Add a room at the end of the dungeon.
    void addRoom(Room *room)
    {
        RoomNode *newNode = new RoomNode(room);

        if (!head)
        {
            head = newNode;
        }

        else
        {
            RoomNode *current = head;

            while (current->next)
                current = current->next;
            current->next = newNode;
        }
    }

    // Return pointer to the first room.
    Room *getStart()
    {
        return head ? head->room : nullptr;
    }

    // Get the next room after the room with the given id.
    Room *getNextRoom(int currentId)
    {
        RoomNode *current = head;

        while (current)
        {
            if (current->room->getId() == currentId && current->next)
            {
                return current->next->room;
            }

            current = current->next;
        }

        return nullptr;
    }
};

// -----------------------------------------------------------------
// Game class: manages the game loop and world navigation.
// -----------------------------------------------------------------

class Game
{
private:
    Player *player;
    Dungeon *dungeon;
    Room *currentRoom;

public:
    Game()
    {
        // Create the player.
        player = new Player("Hero", 100);

        // Create the dungeon and add several rooms.
        dungeon = new Dungeon();

        // Room 1: an empty corridor with a treasure.
        dungeon->addRoom(new Room(1,
                                  "A dimly lit corridor. You see something shimmering on the floor.",
                                  nullptr, new Item("Silver Coin", 10)));

        // Room 2: a room with a Goblin.
        dungeon->addRoom(new Room(2,
                                  "A musty room with cobwebs. A sneaky Goblin lurks here.",
                                  new Enemy("Goblin", 40), nullptr));

        // Room 3: a room with a Troll.
        dungeon->addRoom(new Room(3,
                                  "A large hall with echoing footsteps. A fearsome Troll stands before you.",
                                  new Troll("Troll", 60), nullptr));

        // Room 4: a treasure room with a weapon.
        dungeon->addRoom(new Room(4,
                                  "A glittering chamber filled with treasures. A mighty sword rests on a pedestal.",
                                  nullptr, new Weapon("Excalibur", 150, 10)));

        // Set current room to the start of the dungeon.
        currentRoom = dungeon->getStart();
    }

    ~Game()
    {
        delete player;
        delete dungeon;
    }

    // Display the current room details.
    void describeCurrentRoom()
    {
        cout << "\n=== Room " << currentRoom->getId() << " ===\n";
        cout << currentRoom->getDescription() << "\n";

        if (currentRoom->hasEnemy())
        {
            cout << "An enemy is here: " << currentRoom->getEnemy()->getName()
                 << " (Health: " << currentRoom->getEnemy()->getHealth() << ")\n";
        }

        if (currentRoom->hasItem())
        {
            cout << "There is an item on the ground: " << currentRoom->getItemName() << "\n";
        }
    }

    // Display the game menu.
    void displayMenu()
    {
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

    // Main game loop.
    void run()
    {
        cout << "Welcome to the Dungeon Crawler!\n";
        bool gameOver = false;

        while (!gameOver && player->isAlive())
        {
            // Describe the current room.
            cout << "\n---------------------------\n";
            cout << "You are in Room " << currentRoom->getId() << ".\n";
            cout << currentRoom->getDescription() << "\n";

            if (currentRoom->hasEnemy())
            {
                cout << "An enemy (" << currentRoom->getEnemy()->getName() << ") is here!\n";
            }

            if (currentRoom->hasItem())
            {
                cout << "There is an item lying on the floor: "
                     << currentRoom->getItemName() << "\n";
            }

            cout << "---------------------------\n";

            displayMenu();

            int choice;
            cin >> choice;
            cout << "\n";

            switch (choice)
            {
            case 1:
            {
                // Attack enemy if present.
                if (currentRoom->hasEnemy())
                {
                    while (currentRoom->hasEnemy() && player->isAlive())
                    {
                        // Player attacks enemy.
                        player->attack(currentRoom->getEnemy());

                        // Check if enemy is defeated.
                        if (!currentRoom->getEnemy()->isAlive())
                        {
                            cout << "You defeated the " << currentRoom->getEnemy()->getName() << "!\n";
                            break;
                        }
                        // Enemy attacks back.
                        currentRoom->getEnemy()->attack(player);

                        if (!player->isAlive())
                        {
                            cout << "You have been defeated in battle...\n";
                            gameOver = true;
                            break;
                        }
                    }
                }
                else
                {
                    cout << "There is no enemy here to attack!\n";
                }
                break;
            }
            case 2:
            {
                // Pick up the item if available.
                if (currentRoom->hasItem())
                {
                    Item *item = currentRoom->takeItem();

                    if (item)
                    {
                        cout << "You pick up the " << item->name << ".\n";
                        player->addItem(item);
                    }
                }

                else
                {
                    cout << "There is no item here.\n";
                }

                break;
            }
            case 3:
            {
                // Move to the next room.
                Room *nextRoom = dungeon->getNextRoom(currentRoom->getId());

                if (nextRoom)
                {
                    currentRoom = nextRoom;
                    cout << "You move to Room " << currentRoom->getId() << ".\n";
                }

                else
                {
                    cout << "There are no more rooms. You have reached the end of the dungeon!\n";
                    gameOver = true;
                }

                break;
            }
            case 4:
            {
                // Show inventory.
                player->showInventory();
                break;
            }
            case 5:
            {
                cout << "You wait and gather your thoughts...\n";
                // If an enemy is present, it may take advantage.

                if (currentRoom->hasEnemy())
                {
                    cout << "The enemy seizes the moment!\n";
                    currentRoom->getEnemy()->attack(player);
                }

                break;
            }
            case 6:
            {
                // Equip a weapon from inventory.
                player->equipWeapon();
                break;
            }
            case 7:
            {
                // Display currently equipped weapon.
                player->showEquippedWeapon();
                break;
            }
            case 8:
            {
                // Look around the current room.
                describeCurrentRoom();
                break;
            }
            case 9:
            {
                cout << "Quitting the game. Farewell, adventurer!\n";
                gameOver = true;
                break;
            }
            default:
                cout << "Invalid choice! You hesitate and lose your chance to act.\n";
                break;
            }

            // Check if the player is still alive.
            if (!player->isAlive())
            {
                cout << "\nGame Over. You have perished in the dungeon.\n";
                gameOver = true;
            }
        }

        if (player->isAlive())
        {
            cout << "\nCongratulations! You survived the dungeon crawl.\n";
        }
    }
};

// -----------------------------------------------------------------
// Main function
// -----------------------------------------------------------------

int main()
{
    // Seed the random number generator.
    srand(static_cast<unsigned int>(time(0)));

    Game game;
    game.run();

    return 0;
}
