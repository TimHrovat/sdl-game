#pragma once

#include "../collision/Collision.h"

#include "../vector2D/Vector2D.h"
#include "CollisionComponent.h"
#include "Components.h"
#include "ECS.h"
#include <iostream>

class CollisionComponent;

class PhysicsComponent : public Component {
  private:
    TransformComponent *transform;
    CollisionComponent *collision;
    KeyboardHandler *kbdHandler;

    float gravity = 0.2f;

  public:
    PhysicsComponent(){};
    ~PhysicsComponent(){};

    void init() override;
    void update() override;
};