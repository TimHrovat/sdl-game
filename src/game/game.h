#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class CollisionComponent;

class Game {
  private:
    bool isRunning;
    SDL_Window *window;

  public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<CollisionComponent *> collisions;
};