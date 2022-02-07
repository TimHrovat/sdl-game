#include "GameObject.h"
#include "../src/textureManager/TextureManager.h"

GameObject::GameObject(const char *texturesheet, int x, int y) {

    this->objectTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

GameObject::~GameObject() {
}

void GameObject::Update() {
    xpos++;
    ypos++;

    srcRect.h = 39;
    srcRect.w = 38;
    srcRect.x = 0;
    srcRect.y = 54;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}