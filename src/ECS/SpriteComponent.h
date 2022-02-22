#pragma once

#include "../textureManager/TextureManager.h"
#include "SDL.h"
#include "Components.h"

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

  public:
    SpriteComponent() = default;
    SpriteComponent(const char *path) {
        setTex(path);
    }

    void setTex(const char *path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {

        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = 0;
        srcRect.y = 50;
        srcRect.w = srcRect.h = 40;
        destRect.w = destRect.h = srcRect.h * 2;
    }

    void update() override {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
    }

    void draw() override {
        TextureManager::draw(texture, srcRect, destRect);
    }
};