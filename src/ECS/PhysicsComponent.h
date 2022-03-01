#pragma once

#include "../collision/Collision.h"
#include "CollisionComponent.h"
#include "Components.h"
#include "ECS.h"
#include <iostream>

class PhysicsComponent : public Component {
  private:
    TransformComponent *transform;
    CollisionComponent *collision;
    float gravity = 0.2f;

  public:
    PhysicsComponent(){};
    ~PhysicsComponent(){};

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        collision = &entity->getComponent<CollisionComponent>();
    }

    void update() override {
        // gravity
        // if (transform->position.y < 600.0f - 439 * 0.2f + 1) {
        //     transform->velocity.y += gravity;
        // } else if (transform->velocity.y > 0) {
        //     transform->velocity.y = 0;
        //     entity->getComponent<KeyboardHandler>().inJump = false;
        // }

        // for (auto cc : Game::collisions) {
        //     if (Collision::Side(entity->getComponent<CollisionComponent>(), *cc) && cc->tag == (char *)"tile") {
        //         transform->velocity.x = 0;
        //     }
        //     if (Collision::UpDown(entity->getComponent<CollisionComponent>(), *cc) && cc->tag == (char *)"tile") {
        //         transform->velocity.y = 0;
        //         entity->getComponent<KeyboardHandler>().inJump = false;
        //     } else {
        //         transform->velocity.y += gravity;
        //     }
        // }
    }
};