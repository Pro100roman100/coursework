#pragma once

#include "gameObject.h"
#include "damageable.h"

class Bullet : public GameObject
{
private:
    sf::Vector2f velocityVector = sf::Vector2f();
    float lifetime = 5.f;
    float elapsed = 0.f;
    float velocity;
    int damage;
    Team ownerTeam;
    bool hasHit = false;

public:
    Bullet(const sf::Texture& texture, float velocity, int damage, Team ownerTeam);

    void update(float deltaTime) override;
    Collider getCollider() const override;
    PhysicsObject::ObjectType getType() const override;
    void onCollision(PhysicsObject* target) override;

    void setVelocity(sf::Vector2f direction);
    void setOwnerTeam(Team ownerTeam);
};

class PistolBulletFactory : public ObjectFactory {
public:
    PistolBulletFactory() = delete;
    static std::shared_ptr<GameObject> createObject();
};
class RifleBulletFactory : public ObjectFactory {
public:
    RifleBulletFactory() = delete;
    static std::shared_ptr<GameObject> createObject();
};
class ShotgunBulletFactory : public ObjectFactory {
public:
    ShotgunBulletFactory() = delete;
    static std::shared_ptr<GameObject> createObject();
};
