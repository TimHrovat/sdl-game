#pragma once

#include "SDL.h"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class CollisionComponent;
class Entity;

struct animalRestore {
    float x, y;
};

struct enemyRestore {
    int deltaPos;
    int velocity;
};

struct playerRestore {
    float x, y;
};

struct generalRestore {
    char playerName[51];
    int time, lives, level;
};

struct replay {
    float velocityX;
    float velocityY;
    float positionX, positionY;
};

struct scoreWin {
    int time;
    char name[16];
};

class Game {
  private:
    bool isRunning = false;
    int level;
    int prevTime;
    bool replayRunning = false;
    bool replayAvalible = false;

  public:
    Game();
    ~Game();

    void init(int level, bool restored);

    void update();
    void render();
    void clean();

    void reset(const char *txt);

    void SaveForRestore();
    void Restore();

    void SaveForReplay();
    void ReplayUpdate();
    void Replay();
    void ReplayClean();

    void AddScoreWin();

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