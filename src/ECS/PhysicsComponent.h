#pragma once

#include "../collision/Collision.h"
#include "Components.h"
#include "ECS.h"

class PhysicsComponent : public Component {
  private:
    TransformComponent *transform;
    float gravity = 0.2f;

  public:
    PhysicsComponent(){};
    ~PhysicsComponent(){};

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        // gravity
        if (transform->position.y < 600.0f - 439 * 0.2f + 1) {
            transform->velocity.y += gravity;
        } else if (transform->velocity.y > 0) {
            transform->velocity.y = 0;
            entity->getComponent<KeyboardHandler>().inJump = false;
        }
        for (auto cc : Game::collisions) {
            Collision::AABB(entity->getComponent<CollisionComponent>(), *cc);
        }
    }
};