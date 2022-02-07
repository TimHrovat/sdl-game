#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *fileName, SDL_Renderer *renderer) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}