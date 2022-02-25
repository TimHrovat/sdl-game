#pragma once

#include "../src/game/Game.h"

class TextureManager {
  public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip);
};