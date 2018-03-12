//
// Created by l3gume on 23/02/18.
//

#ifndef VAPEENGINE_COLLISIONHANDLERCOMPONENT_H
#define VAPEENGINE_COLLISIONHANDLERCOMPONENT_H

#include <ecs/ecs.h>
#include <physics/Sphere.h>
#include "ColliderComponent.h"

using namespace ECS;

enum CollisionType {
    BOX_TO_BOX,
    SPHERE_TO_SPHERE,
    BOX_TO_SPHERE
};

/*
 * data object to pass the info of a collision
 */
struct Collision {
    CollisionType type;
    colType e1_type;
    colType e2_type;
    // Pointers to the entities that are involved
    Entity* e1;
    Entity* e2;

    // quick access to the AABBs or spheres
    AABB e1_AABB;
    AABB e2_AABB;
    Sphere e1_Sphere;
    Sphere e2_Sphere;

    // we have to know if they're triggers or not.
    bool e1_isTrigger;
    bool e2_isTrigger;
    bool e1_isStatic;
    bool e2_isStatic;
    float intersectX;
    float intersectY;
    float intersectZ;
    float dx;
    float dy;
    float dz;

    // for spheres
    float sqDist;
    glm::vec3 normal;
};

/*
 * Holds function pointers that will be set by scripts to handle the entity's collisions.
 *
 * Makes it so an object doesn't need to have a handler component to have collisions.
 */
struct CollisionHandlerComponent : Component {
    CollisionHandlerComponent() = default;

    void (*onCollision)(Collision) = nullptr;
    void (*onTriggerEnter)(Collision) = nullptr;
    void (*onTriggerStay)(Collision) = nullptr;
};

#endif //VAPEENGINE_COLLISIONHANDLERCOMPONENT_H