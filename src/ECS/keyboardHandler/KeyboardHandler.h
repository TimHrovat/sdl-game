#pragma once

#include "../../game/Game.h"
#include "../Components.h"
#include "../ECS.h"
#include "../spriteComponent/SpriteComponent.h"
#include "../transformComponent/TransformComponent.h" // no touchy - doesn't work without that shit
#include <iostream>

class KeyboardHandler : public Component {

  public:
    bool inJump = false;
    TransformComponent *transform;
    SpriteComponent *sprite;

    int playerLives = 3;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    if (!inJump) {
                        transform->velocity.y = -3;
                        inJump = true;
                    }
                    break;
                case SDLK_s:
                    break;
                case SDLK_a:
                    transform->velocity.x = -1.3;
                    break;
                case SDLK_d:
                    transform->velocity.x = 1.3;
                    break;

                default:
                    break;
            }
        }

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    break;
                case SDLK_s:
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    break;
                default:
                    break;
            }
        }
    }
};
