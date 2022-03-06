#pragma once

#include "SDL.h"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class CollisionComponent;
class Entity;

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

    void reset(const char *txt);

    bool running();

    static std::vector<CollisionComponent *> collisions;
    static std::vector<Entity *> animalCollisions;
    static std::vector<Entity *> enemyCollisions;

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static void AddTile(int id, int x, int y, int w, int h);
    static void AddAnimal(int platformX, int platformY);
    static void AddEnemy(int platformX, int platformY, int maxDelta);
    static SDL_Rect camera;
};