#pragma once

#include "../game/Game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>

class Text {
  private:
    TTF_Font *roboto;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Color color{255, 255, 255, 255};

  public:
    Text(){};
    Text(const char *text, int x, int y, int w, int h, int size);
    ~Text();

    void update(const char *text);
    void draw();
};