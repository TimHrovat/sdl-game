#pragma once

#include "SDL.h"

class CollisionComponent;

class Collision {
  public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
    static bool AABB(const CollisionComponent &colA, const CollisionComponent &colB);
    static bool Side(const CollisionComponent &colA, const CollisionComponent &colB);
    static bool UpDown(const CollisionComponent &colA, const CollisionComponent &colB);
};