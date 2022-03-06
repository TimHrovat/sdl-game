// #pragma once

// #include "../game/Game.h"
// #include "../text/text.h"
// #include "SDL.h"
// #include <iostream>
// #include <vector>

// class Text;

// class Menu {

//   private:
//     bool isRunning;
//     SDL_Window *window;

//   public:
//     Menu(){};
//     ~Menu(){};

//     void init(const char *title, int xpos, int ypos, int width, int height);

//     bool running();

//     void handleEvents();
//     void update();
//     void render();
//     void clean();

//     static SDL_Renderer *renderer;
//     static Game *game;
//     static SDL_Event event;
// };

//! if you want to incloude menu change main.cpp, text.h