#include "game.h"
#undef main

Game* game = nullptr;
int main(int argc, char* argv[])
{
    r:
    game = new Game();
    game->init("Snowy Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 750, false);
    int flag = 0;

    while (game->running())
    {
        game->handleEvents();
        //game->update();
        if (flag == 0)
        {
            game->startgame();
            game->setboard();
            flag = -1;
        }


        game->mouse();
        game->gameover();
        break;
    }
    game->clean();
    goto r;
    return 0;
}