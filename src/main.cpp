#include "Game.h"
#include "TitleState.h"
#include <iostream>

int main(int argc, char **argv) {
    Game& game = Game::GetInstance();
    TitleState* title = new TitleState();
    
    game.Push(title);
    game.Run();
    return 0;
}
