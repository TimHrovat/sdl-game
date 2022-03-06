#include "text.h"

Text::Text(const char *text, int x, int y, int w, int h, int size) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    roboto = TTF_OpenFont("../assets/Roboto.ttf", size);
    surface = TTF_RenderText_Solid(roboto, text, color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
}

Text::~Text() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Text::draw() {
    SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

void Text::update(const char *text) {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = TTF_RenderText_Solid(roboto, text, color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
}