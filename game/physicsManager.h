#pragma once

#include <vector>
#include <memory>
#include "physicsObject.h"
#include "consts.h"
#include "singleton.h"

class PhysicsManager : public Singleton<PhysicsManager> {
    friend class Singleton<PhysicsManager>;

private:

    PhysicsManager() = default;
    std::vector<PhysicsObject*> physicsObjects;

public:
    void addPhysicsObject(PhysicsObject* obj);
    void removePhysicsObject(PhysicsObject* obj);

    std::vector<PhysicsObject*> checkOverlap(const Collider& collider) const;
    bool checkPath(sf::Vector2f start, sf::Vector2f end) const;

    void update(float deltaTime);
    void drawColliders(sf::RenderWindow* window);
    void clear();


private:
    struct CollisionManifold {
        bool isColliding;
        sf::Vector2f normal;
        float depth;
    };

    static CollisionManifold checkCollision(const BoxCollider& a, const BoxCollider& b);
    static CollisionManifold checkCollision(const CircleCollider& a, const CircleCollider& b);
    static CollisionManifold checkCollision(const BoxCollider& box, const CircleCollider& circle);

    static void resolveCollision(PhysicsObject* objA, PhysicsObject* objB, const CollisionManifold& manifold);
};