#include "TextureManager.h"

// creates a texture from given png
SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &dstRect, NULL, NULL, flip);
}