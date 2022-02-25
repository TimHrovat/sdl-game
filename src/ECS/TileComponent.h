#pragma once

#include "ECS.h"
#include "SDL.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

class TileComponent : public Component {
  public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    Vector2D position;

    SDL_Rect tileRect;
    int tileID;
    char *path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        position.x = x;
        position.y = y;

        switch (tileID) {
            case 0:
                path = (char *)"../assets/background/ground.png";
                break;
            default:
                break;
        }
    }

    void init() override {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.h, tileRect.w, 1.0f);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();

        entity->addComponent<CollisionComponent>("tile");
    }

    void update() override {
        transform->position.x = position.x - Game::camera.x;
        transform->position.y = position.y - Game::camera.y;
    }
};