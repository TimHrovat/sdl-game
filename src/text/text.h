#pragma once

#include "../game/Game.h"
#include "../menu/Menu.h"
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
    bool center = false;

  public:
    const char *text;
    Text(){};
    Text(const char *txt, int x, int y, int size, bool center);
    Text(std::string txt, int x, int y, int size, bool center);
    ~Text();

    void update(const char *text);
    void draw();
    void changeColorBrightness(int);
};