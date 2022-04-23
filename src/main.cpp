#include <SDL2/SDL.h>
#include <iostream>

#include "menu/Menu.h"

Menu *menu = NULL;

int main() {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    menu = new Menu();
    menu->init("SDL game project", 0, 0, 1080, 720);

    while (menu->running()) {

        frameStart = SDL_GetTicks();

        menu->handleEvents();
        menu->update();
        menu->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    menu->clean();

    return 0;
}