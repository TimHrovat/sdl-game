#pragma once

#include "../game/Game.h"

class Map {
  public:
    Map();
    ~Map();

    void DrawMap();
    static void addAnimals();
    static void addEnemies();
};