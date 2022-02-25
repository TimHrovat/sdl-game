#pragma once

#include "../vector2D/Vector2D.h"
#include "Components.h"
#include <cmath>

class TransformComponent : public Component {
  public:
    Vector2D position;
    Vector2D velocity;

    int height = 40;
    int width = 40;
    float scale = 1.0f;

    int speed = 6;

    TransformComponent() {
        position.Zero();
    }

    TransformComponent(float scale) {
        position.x = 200;
        position.y = 510;
        this->scale = scale;
    }

    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int h, int w, float scale) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        this->scale = scale;
    }

    void init() override {
        velocity.Zero();
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};