#include "PhysicsComponent.h"

void PhysicsComponent::init() {
    transform = &entity->getComponent<TransformComponent>();
    collision = &entity->getComponent<CollisionComponent>();
    kbdHandler = &entity->getComponent<KeyboardHandler>();
}

void PhysicsComponent::update() {
    transform->velocity.y += gravity; // gravity

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