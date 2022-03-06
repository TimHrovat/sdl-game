#pragma once

#include "../game/Game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>

class Text {
  private:
    std::stringstream strs;
    TTF_Font *roboto;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Color color{255, 255, 255, 100};

  public:
    Text(){};
    Text(const char *text, int x, int y, int w, int h, int size) {
        strs << text;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        roboto = TTF_OpenFont("../assets/Roboto.ttf", size);
        surface = TTF_RenderText_Solid(roboto, (char *)strs.str().c_str(), color);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    };
    ~Text() {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    };

    void draw() {
        SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
    }
};