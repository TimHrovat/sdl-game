#include <SDL2/SDL.h>
#include <iostream>

#include "game/Game.h"

Game *game = NULL;

int main() {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("SDL game project", 0, 0, 1080, 720);

    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}