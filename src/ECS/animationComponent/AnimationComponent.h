#pragma once

#include "../../game/Game.h"
#include "../../textureManager/TextureManager.h"
#include "../Components.h"
#include "../spriteComponent/SpriteComponent.h"
#include "../transformComponent/TransformComponent.h"
#include "SDL.h"
#include <map>
#include <string>

struct Animation {
    SDL_Texture *texture;
    int frames;
    int speed;
    int srcWidth, srcHeight;

    Animation() {}
    Animation(const char *path, int frames, int speed, int srcWidth, int srcHeight) {
        texture = TextureManager::LoadTexture(path);
        this->frames = frames;
        this->speed = speed;
        this->srcWidth = srcWidth;
        this->srcHeight = srcHeight;
    }
};

class AnimationComponent : public Component {
  private:
    bool isPlayer = false;
    SpriteComponent *sprite;
    TransformComponent *transform;
    int speed, frames;
    std::string lastAnimation;

  public:
    std::map<const char *, Animation> animations;

    AnimationComponent() {
        isPlayer = true;

        Animation idle = Animation((char *)"../assets/player/player_idle.png", 10, 100, 232, 439);
        Animation run = Animation((char *)"../assets/player/player_run.png", 10, 50, 363, 458);
        Animation kunaiThrow = Animation((char *)"../assets/player/player_throw.png", 10, 50, 377, 451);
        Animation jump = Animation((char *)"../assets/player/player_jump.png", 10, 50, 362, 483);
        Animation jumpKunaiThrow = Animation((char *)"../assets/player/player_jump_throw.png", 10, 50, 360, 431);
        Animation death = Animation((char *)"../assets/player/player_death.png", 10, 50, 482, 498);

        animations.emplace("Idle", idle);
        animations.emplace("Run", run);
        animations.emplace("KunaiThrow", kunaiThrow);
        animations.emplace("Jump", jump);
        animations.emplace("JumpKunaiThrow", jumpKunaiThrow);
        animations.emplace("Death", death);
    }

    AnimationComponent(const char *pathWalk, bool isMoving) {
        if (isMoving) {
            Animation walk = Animation(pathWalk, 10, 150, 415, 507);
            // animations.emplace("Idle", walk);
            animations.emplace("Run", walk);
        } else {
            Animation idle = Animation(pathWalk, 10, 100, 542, 474);
            animations.emplace("Idle", idle);
        }
    }

    void init() override {
        sprite = &entity->getComponent<SpriteComponent>();
        transform = &entity->getComponent<TransformComponent>();

        // SetAnimation("Idle");
    }

    void update() override {
        sprite->srcRect.x = sprite->srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        if (transform->velocity.x == 0 && transform->velocity.y == 0 && lastAnimation.compare("Idle") != 0) {
            SetAnimation("Idle");
            lastAnimation = (char *)"Idle";
        } else if (transform->velocity.x > 0 && transform->velocity.y < 0 && lastAnimation.compare("JumpRight") != 0) {
            sprite->spriteFlip = SDL_FLIP_NONE;
            SetAnimation("Jump");
            lastAnimation = (char *)"JumpRight";
        } else if (transform->velocity.x > 0 && transform->velocity.y == 0 && lastAnimation.compare("RunRight") != 0) {
            sprite->spriteFlip = SDL_FLIP_NONE;
            SetAnimation("Run");
            lastAnimation = (char *)"RunRight";
        } else if (transform->velocity.x < 0 && transform->velocity.y == 0 && lastAnimation.compare("RunLeft") != 0) {
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            SetAnimation("Run");
            lastAnimation = (char *)"RunLeft";
        }
    }

    void SetAnimation(const char *animationName) {
        sprite->texture = animations[animationName].texture;
        this->frames = animations[animationName].frames;
        this->speed = animations[animationName].speed;
        sprite->srcRect.w = animations[animationName].srcWidth;
        sprite->srcRect.h = animations[animationName].srcHeight;
        sprite->srcRect.x = 0;
        sprite->srcRect.y = 0;
    }
};
