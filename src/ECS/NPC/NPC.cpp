#include "NPC.h"

NPC::NPC(const char *tag, float platformX, float platformY, float maxDelta) {
    this->tag = tag;
    position.x = platformX;
    position.y = platformY;
    this->maxDelta = maxDelta;
}

void NPC::init() {
    if (tag.compare("enemy") == 0) {
        registerEnemy();
    } else if (tag.compare("animal") == 0) {
        registerAnimal();
    }
}

void NPC::update() {
    transform->width = sprite->srcRect.w;
    transform->height = sprite->srcRect.h;

    // movement for enemies
    if (tag.compare("enemy") == 0) {
        if (deltaPos == maxDelta) {
            transform->velocity.x = -1;
        } else if (deltaPos == 0) {
            transform->velocity.x = 1;
        }

        deltaPos += transform->velocity.x;

        transform->position.x = position.x - Game::camera.x + deltaPos;
    } else {
        transform->position.x = position.x - Game::camera.x;
    }
    transform->position.y = position.y - Game::camera.y;
}

void NPC::registerEnemy() {
    entity->addComponent<TransformComponent>(position.x, position.y, 0, 0, 0.13);
    entity->addComponent<SpriteComponent>();
    entity->addComponent<CollisionComponent>(tag);
    entity->addComponent<AnimationComponent>("../assets/enemy/enemy_run.png", true);

    transform = &entity->getComponent<TransformComponent>();
    animation = &entity->getComponent<AnimationComponent>();
    sprite = &entity->getComponent<SpriteComponent>();

    maxDelta -= static_cast<int>(animation->animations["Run"].srcWidth * transform->scale);
    position.y = position.y - animation->animations["Run"].srcHeight * transform->scale + 3;

    Game::enemyCollisions.push_back(entity);
}

void NPC::registerAnimal() {
    entity->addComponent<TransformComponent>(position.x, position.y, 0, 0, 0.09);
    entity->addComponent<SpriteComponent>();
    entity->addComponent<CollisionComponent>(tag);
    entity->addComponent<AnimationComponent>("../assets/animal/animal_idle.png", false);

    transform = &entity->getComponent<TransformComponent>();
    animation = &entity->getComponent<AnimationComponent>();
    sprite = &entity->getComponent<SpriteComponent>();

    position.y = position.y - animation->animations["Idle"].srcHeight * transform->scale + 3;

    Game::animalCollisions.push_back(entity);
}