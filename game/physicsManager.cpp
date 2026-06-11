#include "physicsManager.h"
#include <algorithm>
#include <cmath>

void PhysicsManager::addPhysicsObject(PhysicsObject* obj) {
    physicsObjects.push_back(obj);
}

void PhysicsManager::removePhysicsObject(PhysicsObject* obj) {
    auto it = std::find(physicsObjects.begin(), physicsObjects.end(), obj);
    if (it != physicsObjects.end()) {
        physicsObjects.erase(it);
    }
}

std::vector<PhysicsObject*> PhysicsManager::checkOverlap(const Collider& collider) const {
    std::vector<PhysicsObject*> overlappingObjects;
    
    for (auto* obj : physicsObjects) {
        if (!obj) continue;

        Collider objCollider = obj->getCollider();
        CollisionManifold manifold = { false, sf::Vector2f(0.f, 0.f), 0.f };

        std::visit([&](auto&& c1, auto&& c2) {
            using T1 = std::decay_t<decltype(c1)>;
            using T2 = std::decay_t<decltype(c2)>;

            if constexpr (std::is_same_v<T1, BoxCollider> && std::is_same_v<T2, BoxCollider>) {
                manifold = checkCollision(c1, c2);
            } else if constexpr (std::is_same_v<T1, CircleCollider> && std::is_same_v<T2, CircleCollider>) {
                manifold = checkCollision(c1, c2);
            } else if constexpr (std::is_same_v<T1, BoxCollider> && std::is_same_v<T2, CircleCollider>) {
                manifold = checkCollision(c1, c2);
            } else if constexpr (std::is_same_v<T1, CircleCollider> && std::is_same_v<T2, BoxCollider>) {
                manifold = checkCollision(c2, c1);
                manifold.normal = -manifold.normal;
            }
        }, collider, objCollider);

        if (manifold.isColliding) {
            overlappingObjects.push_back(obj);
        }
    }

    return overlappingObjects;
}

void PhysicsManager::clear() {
    physicsObjects.clear();
}

PhysicsManager::CollisionManifold PhysicsManager::checkCollision(const BoxCollider& a, const BoxCollider& b) {
    CollisionManifold manifold = { false, sf::Vector2f(0.f, 0.f), 0.f };
    sf::Vector2f diff = b.getCenter() - a.getCenter();
    sf::Vector2f minDiff = (a.getSize() + b.getSize()) / 2.0f;
    float overlapX = minDiff.x - std::abs(diff.x);
    if (overlapX > 0) {
        float overlapY = minDiff.y - std::abs(diff.y);
        if (overlapY > 0) {
            manifold.isColliding = true;
            if (overlapX < overlapY) {
                manifold.normal = diff.x < 0 ? sf::Vector2f(-1.f, 0.f) : sf::Vector2f(1.f, 0.f);
                manifold.depth = overlapX;
            } else {
                manifold.normal = diff.y < 0 ? sf::Vector2f(0.f, -1.f) : sf::Vector2f(0.f, 1.f);
                manifold.depth = overlapY;
            }
        }
    }
    return manifold;
}

PhysicsManager::CollisionManifold PhysicsManager::checkCollision(const CircleCollider& a, const CircleCollider& b) {
    CollisionManifold manifold = { false, sf::Vector2f(0.f, 0.f), 0.f };
    sf::Vector2f diff = b.getCenter() - a.getCenter();
    float distSq = diff.x * diff.x + diff.y * diff.y;
    float radSum = a.getRadius() + b.getRadius();
    if (distSq <= radSum * radSum) {
        manifold.isColliding = true;
        float dist = std::sqrt(distSq);
        if (dist != 0.f) {
            manifold.normal = diff / dist;
            manifold.depth = radSum - dist;
        } else {
            manifold.normal = sf::Vector2f(0.f, 1.f);
            manifold.depth = radSum;
        }
    }
    return manifold;
}

PhysicsManager::CollisionManifold PhysicsManager::checkCollision(const BoxCollider& box, const CircleCollider& circle) {
    CollisionManifold manifold = { false, sf::Vector2f(0.f, 0.f), 0.f };
    sf::Vector2f center = circle.getCenter();
    sf::Vector2f boxCenter = box.getCenter();
    sf::Vector2f boxHalf = box.getSize() / 2.0f;

    float testX = center.x;
    float testY = center.y;

    if (testX < boxCenter.x - boxHalf.x) testX = boxCenter.x - boxHalf.x;
    else if (testX > boxCenter.x + boxHalf.x) testX = boxCenter.x + boxHalf.x;

    if (testY < boxCenter.y - boxHalf.y) testY = boxCenter.y - boxHalf.y;
    else if (testY > boxCenter.y + boxHalf.y) testY = boxCenter.y + boxHalf.y;

    float distX = center.x - testX;
    float distY = center.y - testY;
    float distanceSq = (distX * distX) + (distY * distY);

    if (distanceSq <= (circle.getRadius() * circle.getRadius())) {
        manifold.isColliding = true;
        float dist = std::sqrt(distanceSq);

        if (dist == 0.f) {
            sf::Vector2f diff = center - boxCenter;
            float overlapX = boxHalf.x - std::abs(diff.x);
            float overlapY = boxHalf.y - std::abs(diff.y);

            if (overlapX < overlapY) {
                manifold.normal = diff.x < 0 ? sf::Vector2f(-1.f, 0.f) : sf::Vector2f(1.f, 0.f);
                manifold.depth = circle.getRadius() + overlapX;
            } else {
                manifold.normal = diff.y < 0 ? sf::Vector2f(0.f, -1.f) : sf::Vector2f(0.f, 1.f);
                manifold.depth = circle.getRadius() + overlapY;
            }
        } else {
            manifold.normal = sf::Vector2f(distX / dist, distY / dist);
            manifold.depth = circle.getRadius() - dist;
        }
    }
    return manifold;
}

void PhysicsManager::resolveCollision(PhysicsObject* objA, PhysicsObject* objB, const CollisionManifold& manifold) {
    if (!manifold.isColliding) return;

    PhysicsObject::ObjectType typeA = objA->getType();
    PhysicsObject::ObjectType typeB = objB->getType();

    bool staticA = typeA == PhysicsObject::ObjectType::_static_;
    bool staticB = typeB == PhysicsObject::ObjectType::_static_;
    bool triggerA = typeA == PhysicsObject::ObjectType::_trigger_;
    bool triggerB = typeB == PhysicsObject::ObjectType::_trigger_;

    objA->onCollision(objB);
    objB->onCollision(objA);

    if (staticA && staticB) return;

    if (triggerA || triggerB) return;

    if (!staticA && !staticB) {
        sf::Vector2f moveVec = manifold.normal * (manifold.depth / 2.f);
        objA->move(-moveVec);
        objB->move(moveVec);
    } else if (!staticA) {
        objA->move(-manifold.normal * manifold.depth);
    } else if (!staticB) {
        objB->move(manifold.normal * manifold.depth);
    }
}

void PhysicsManager::drawColliders(sf::RenderWindow* window) {
    for (auto* obj : physicsObjects) {
        if (!obj) 
            continue;

        sf::Color color;
        switch (obj->getType()) {
        case PhysicsObject::ObjectType::_dynamic_:
            color = sf::Color::Green;
            break;
        case PhysicsObject::ObjectType::_static_:
            color = sf::Color::Blue;
            break;
        case PhysicsObject::ObjectType::_trigger_:
            color = sf::Color::Red;
            break;
        default:
            color = sf::Color::Black;
            break;
        }

        Collider col = obj->getCollider();
        if (std::holds_alternative<BoxCollider>(col)) {
            BoxCollider box = std::get<BoxCollider>(col);
            sf::RectangleShape rect(box.getSize());
            rect.setOrigin(box.getSize() / 2.f);
            rect.setPosition(box.getCenter());
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(color);
            rect.setOutlineThickness(1 / pixelRatio);
            window->draw(rect);
        } else if (std::holds_alternative<CircleCollider>(col)) {
            CircleCollider circle = std::get<CircleCollider>(col);
            sf::CircleShape circ(circle.getRadius());
            circ.setOrigin({circle.getRadius(), circle.getRadius()});
            circ.setPosition(circle.getCenter());
            circ.setFillColor(sf::Color::Transparent);
            circ.setOutlineColor(color);
            circ.setOutlineThickness(1 / pixelRatio);
            window->draw(circ);
        }
    }
}

void PhysicsManager::update(float deltaTime) {
    for (size_t i = 0; i < physicsObjects.size(); ++i) {
        if (!physicsObjects[i]) continue;

        for (size_t j = i + 1; j < physicsObjects.size(); ++j) {
            if (!physicsObjects[j]) continue;

            auto& objA = physicsObjects[i];
            auto& objB = physicsObjects[j];

            PhysicsObject::ObjectType typeA = objA->getType();
            PhysicsObject::ObjectType typeB = objB->getType();

            if (typeA == PhysicsObject::ObjectType::_static_ && typeB == PhysicsObject::ObjectType::_static_) continue;
            if (typeA == PhysicsObject::ObjectType::_trigger_ && typeB == PhysicsObject::ObjectType::_trigger_) continue;

            Collider colA = objA->getCollider();
            Collider colB = objB->getCollider();

            CollisionManifold manifold = { false, sf::Vector2f(0,0), 0.f };

            if (std::holds_alternative<BoxCollider>(colA) && std::holds_alternative<BoxCollider>(colB)) {
                manifold = checkCollision(std::get<BoxCollider>(colA), std::get<BoxCollider>(colB));
            } else if (std::holds_alternative<CircleCollider>(colA) && std::holds_alternative<CircleCollider>(colB)) {
                manifold = checkCollision(std::get<CircleCollider>(colA), std::get<CircleCollider>(colB));
            } else if (std::holds_alternative<BoxCollider>(colA) && std::holds_alternative<CircleCollider>(colB)) {
                manifold = checkCollision(std::get<BoxCollider>(colA), std::get<CircleCollider>(colB));
            } else if (std::holds_alternative<CircleCollider>(colA) && std::holds_alternative<BoxCollider>(colB)) {
                manifold = checkCollision(std::get<BoxCollider>(colB), std::get<CircleCollider>(colA));
                manifold.normal = -manifold.normal;
            }

            if (manifold.isColliding) {
                resolveCollision(objA, objB, manifold);
            }
        }
    }
}

bool PhysicsManager::checkPath(sf::Vector2f start, sf::Vector2f end) const
{
    for (const auto* obj : physicsObjects) {
        if (!obj) continue;

        if (obj->getType() != PhysicsObject::ObjectType::_static_) continue;

        Collider col = obj->getCollider();

        if (std::holds_alternative<BoxCollider>(col)) {
            BoxCollider box = std::get<BoxCollider>(col);
            sf::Vector2f boxCenter = box.getCenter();
            sf::Vector2f boxHalf = box.getSize() / 2.f;

            sf::Vector2f d = end - start;
            sf::Vector2f f = start - boxCenter;

            float a = d.x * d.x + d.y * d.y;
            float b = 2.f * (f.x * d.x + f.y * d.y);
            float c = (f.x * f.x + f.y * f.y) - (boxHalf.x * boxHalf.x + boxHalf.y * boxHalf.y);

            float discriminant = b * b - 4 * a * c;
            if (discriminant >= 0.f) {
                discriminant = std::sqrt(discriminant);
                float t1 = (-b - discriminant) / (2 * a);
                float t2 = (-b + discriminant) / (2 * a);

                if ((t1 >= 0.f && t1 <= 1.f) || (t2 >= 0.f && t2 <= 1.f) ||
                    (t1 < 0.f && t2 > 1.f)) {
                    return false;
                }
            }
        }

        else if (std::holds_alternative<CircleCollider>(col)) {
            CircleCollider circle = std::get<CircleCollider>(col);
            sf::Vector2f circleCenter = circle.getCenter();
            float radius = circle.getRadius();

            sf::Vector2f d = end - start;
            sf::Vector2f f = start - circleCenter;

            float a = d.x * d.x + d.y * d.y;
            float b = 2.f * (f.x * d.x + f.y * d.y);
            float c = (f.x * f.x + f.y * f.y) - (radius * radius);

            float discriminant = b * b - 4 * a * c;
            if (discriminant >= 0.f) {
                discriminant = std::sqrt(discriminant);
                float t1 = (-b - discriminant) / (2 * a);
                float t2 = (-b + discriminant) / (2 * a);

                if ((t1 >= 0.f && t1 <= 1.f) || (t2 >= 0.f && t2 <= 1.f) ||
                    (t1 < 0.f && t2 > 1.f)) {
                    return false;
                }
            }
        }
    }

    return true;
}