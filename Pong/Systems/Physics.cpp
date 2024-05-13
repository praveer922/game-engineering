#include "Physics.h"
#include <Components/Components.h>

namespace Physics {

    // This updates the entity's position and velocity if there are any forces present on it.
    void Update(MovementComponent * movementComponent, ForceComponent * forceComponent, float dt) {
            Vector2* position = &movementComponent->position;
            Vector2* velocity = &movementComponent->velocity;
            Vector2* force = &forceComponent->force;

            // Using Euler integration
            // Update velocity
            velocity->x(velocity->x() + (force->x() / 1.0f) * dt);
            velocity->y(velocity->y() + (force->y() / 1.0f) * dt);

            position->x(position->x() + velocity->x() * dt);
            position->y(position->y() + velocity->y() * dt);

            // now that velocity has been updated, set drag as the only force remaining on the object
            float drag_x = -0.03 * (velocity->x() * velocity->x());
            if (velocity->x() < 0) {
                drag_x = -drag_x;
            }
            float drag_y = -0.03 * (velocity->y() * velocity->y());
            if (velocity->y() < 0) {
                drag_y = -drag_y;
            }

            force->x(drag_x);
            force->y(drag_y);
    }

    bool isCollision(MovementComponent * obj1, MovementComponent * obj2) {
        return (obj1->position.x() < obj2->position.x() + obj2->width &&
            obj1->position.x() + obj1->width > obj2->position.x() &&
            obj1->position.y() < obj2->position.y() + obj2->height &&
            obj1->position.y() + obj1->height > obj2->position.y()
            );
    }

    void handleCollision(MovementComponent* playerMovement, ForceComponent* playerForce) {
        // first get movement direction
        Vector2 collisionForce = -1 * (playerMovement->velocity);
        // scale it 
        collisionForce *= 100000;
        playerForce->force = playerForce->force + collisionForce;
    }
}