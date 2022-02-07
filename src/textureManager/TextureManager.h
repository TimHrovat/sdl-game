#pragma once

#include "../src/game/Game.h"

class TextureManager {
  public:
    static SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *renderer);
};