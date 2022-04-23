#pragma once

#include "../game/Game.h"
#include <fstream>

struct Platform {
    int x, y, w, h; // coordinates of the platform
    bool hasEnemy;  // is there an enemy on the playform
    bool hasAnimal; // is there an animal on the platform
    int animalXPos; // position from left to right of the platform
};

class Map {
  public:
    Map(){};
    Map(int level);
    ~Map(){};

    void DrawMap();
    static void LoadMap(int level);
};