#pragma once

#include "../../collision/Collision.h"

#include "../../vector2D/Vector2D.h"
#include "../Components.h"
#include "../ECS.h"
#include "../collisionComponent/CollisionComponent.h"
#include <iostream>

class CollisionComponent;

class PhysicsComponent : public Component {
  private:
    TransformComponent *transform;
    CollisionComponent *collision;
    KeyboardHandler *kbdHandler;

    float gravity = 0.2f;

  public:
    bool isActive = true;
    PhysicsComponent(){};
    ~PhysicsComponent(){};

    void init() override;
    void update() override;
};