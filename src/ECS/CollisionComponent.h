#pragma once

#include "Components.h"
#include "SDL.h"
#include <string>

class CollisionComponent : public Component {
  public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent *transform;

    CollisionComponent(std::string t) {
        tag = t;
    }

    void init() override {
        if (!entity->hasComponent<TransformComponent>()) { // error check
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        Game::collisions.push_back(this);
    }

    void update() override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};