#include "text.h"
#include <cstring>

Text::Text(const char *txt, int x, int y, int size, bool center) {
    rect.x = x;
    rect.y = y;

    this->text = txt;
    roboto = TTF_OpenFont("../assets/Roboto.ttf", size);
    surface = TTF_RenderText_Blended(roboto, this->text, color);
    texture = SDL_CreateTextureFromSurface(Menu::renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    if (center) {
        rect.x = 540 - rect.w / 2;
    }
}

Text::Text(std::string txt, int x, int y, int size, bool center) {
    rect.x = x;
    rect.y = y;

    this->text = txt.c_str();
    roboto = TTF_OpenFont("../assets/Roboto.ttf", size);
    surface = TTF_RenderText_Blended(roboto, this->text, color);
    if (center) {
        rect.x = 540 - rect.w / 2;
    }
    texture = SDL_CreateTextureFromSurface(Menu::renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

Text::~Text() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Text::draw() {
    SDL_RenderCopy(Menu::renderer, texture, NULL, &rect);
}

void Text::update(const char *newText) {
    this->text = newText;
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = TTF_RenderText_Blended(roboto, this->text, color);
    texture = SDL_CreateTextureFromSurface(Menu::renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    if (center) {
        rect.x = 540 - rect.w / 2;
    }
}

void Text::changeColorBrightness(int b) {
    color.a = b;
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = TTF_RenderText_Blended(roboto, this->text, color);
    texture = SDL_CreateTextureFromSurface(Menu::renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}