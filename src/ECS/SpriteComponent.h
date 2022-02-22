#pragma once

#include "../textureManager/TextureManager.h"
#include "Components.h"
#include "SDL.h"

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
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char *path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {

        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = 0;
        srcRect.y = 50;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = static_cast<int>(transform->width * transform->scale);
        destRect.h = static_cast<int>(transform->height * transform->scale);
    }

    void draw() override {
        TextureManager::draw(texture, srcRect, destRect);
    }
};