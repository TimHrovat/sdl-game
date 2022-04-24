#include "PhysicsComponent.h"

void PhysicsComponent::init() {
    transform = &entity->getComponent<TransformComponent>();
    collision = &entity->getComponent<CollisionComponent>();
    kbdHandler = &entity->getComponent<KeyboardHandler>();
}

void PhysicsComponent::update() {
    if (isActive) {
        transform->velocity.y += gravity; // gravity

        if (transform->position.x <= 0 && transform->velocity.x < 0)
            transform->position.x = 0;
        else if (transform->position.x >= 1880 && transform->velocity.x > 0)
            transform->position.x = 1880;

        for (auto c : Game::collisions) {
            if (c->tag == "tile") {
                if (Collision::AABB(*collision, *c) && transform->velocity.y > 0) {
                    kbdHandler->inJump = false;
                }
                if (Collision::AABB(*collision, *c) && kbdHandler->inJump == false) {
                    transform->velocity.y = 0;
                    transform->position.y = c->transform->position.y - transform->height * transform->scale + 1; // if you dont add 1 the player shakes on y axis
                }
            }
        }
    }

    // checking the collisions with animals
    int i = 0;
    for (auto animal : Game::animalCollisions) {
        if (Collision::AABB(*collision, animal->getComponent<CollisionComponent>())) {
            Game::animalCollisions.erase(Game::animalCollisions.begin() + i, Game::animalCollisions.begin() + i + 1);
            animal->destroy();
        }
        i++;
    }

    // checking the collisions with enemies
    for (auto enemy : Game::enemyCollisions) {
        if (Collision::AABB(*collision, enemy->getComponent<CollisionComponent>())) {
            kbdHandler->playerLives--;
            Game::time += 10;
            transform->position.y = 500;
            transform->position.x = 40;
        }
    }
}
