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
    bool isRunning = false;
    int level;
    int prevTime;

  public:
    Game();
    ~Game();

    void init(int level);

    void update();
    void render();
    void clean();

    void reset(const char *txt);
    void SaveForRestore();

    bool running();

    static std::vector<CollisionComponent *> collisions;
    static std::vector<Entity *> animalCollisions;
    static std::vector<Entity *> enemyCollisions;

    static void AddTile(int id, int x, int y, int w, int h);
    static void AddAnimal(int platformX, int platformY);
    static void AddEnemy(int platformX, int platformY, int maxDelta);
    static void AddPlayer();
    static void AddBackground();
    static SDL_Rect camera;
    static int time;
};