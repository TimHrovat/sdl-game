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
        transform->velocity.y += 0.2;
    }
};