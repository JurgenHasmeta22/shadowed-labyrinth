#include "game/Game.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    Game game;
    game.run();

    return 0;
}
