#pragma once

#include "../vector2D/Vector2D.h"
#include "Components.h"

class TransformComponent : public Component {
  public:
    Vector2D position;
    Vector2D velocity;

    int speed = 3;

    TransformComponent() {
        position.x = 0.0f;
        position.y = 0.0f;
    }

    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void init() override {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};