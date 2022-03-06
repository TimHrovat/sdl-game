#pragma once

#include "../../textureManager/TextureManager.h"
#include "../Components.h"
#include "../transformComponent/TransformComponent.h"
#include "SDL.h"
#include <iostream>
#include <map>

class SpriteComponent : public Component {
  public:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(const char *path) {
        setTex(path);
    }
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char *path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override {
        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = static_cast<int>(srcRect.w * transform->scale);
        destRect.h = static_cast<int>(srcRect.h * transform->scale);
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }
};