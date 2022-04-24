#pragma once

#include "../../vector2D/Vector2D.h"
#include "../Components.h"
#include "../ECS.h"
#include "../animationComponent/AnimationComponent.h"
#include <iostream>
#include <string>

class NPC : public Component {
  private:
    TransformComponent *transform;
    AnimationComponent *animation;
    CollisionComponent *collision;
    SpriteComponent *sprite;

    bool isActive = true;
    bool rotate = false;
    std::string tag;
    float maxDelta;

    void registerEnemy();
    void registerAnimal();

  public:
    Vector2D position;
    int deltaPos = 0;
    NPC(){};
    ~NPC(){};

    NPC(const char *tag, float platformX, float platformY, float maxDelta);

    void init() override;
    void update() override;
};