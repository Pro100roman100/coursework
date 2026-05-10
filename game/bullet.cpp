#include "bullet.h"
#include "physicsManager.h"
#include "objectManager.h"
#include "resourceManager.h"

Bullet::Bullet(const sf::Texture& texture, float velocity, int damage, Team ownerTeam) 
    : GameObject(texture), velocity(velocity), damage(damage), ownerTeam(ownerTeam)
{
}

void Bullet::update(float deltaTime)
{
    elapsed += deltaTime;
    if (elapsed >= lifetime) {
        ObjectManager::getInstance().removeObject(this);
        return;
    }

    move(velocityVector * deltaTime);
}

Collider Bullet::getCollider() const
{
    return CircleCollider(getPosition(), 3.f);
}

PhysicsObject::ObjectType Bullet::getType() const
{
    return PhysicsObject::ObjectType::_trigger_;
}

void Bullet::onCollision(PhysicsObject* target)
{
    if (hasHit)
        return;

    if (auto* damageable = dynamic_cast<Damageable*>(target)) {
        if (damageable->getTeam() != ownerTeam) {
            damageable->takeDamage(damage);
            hasHit = true;
            ObjectManager::getInstance().removeObject(this);
        }
    }
    else {
        hasHit = true;
        ObjectManager::getInstance().removeObject(this);
    }
}

void Bullet::setVelocity(sf::Vector2f direction)
{
    velocityVector = direction.normalized() * velocity;
    sprite.setRotation(direction.angle());
}

void Bullet::setOwnerTeam(Team ownerTeam)
{
    this->ownerTeam = ownerTeam;
}

std::shared_ptr<GameObject> PistolBulletFactory::createObject()
{
    auto bullet = std::make_shared<Bullet>(
        ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_bullet), tileSize * 15.f, 35, Team::neutral);
    return bullet;
}

std::shared_ptr<GameObject> RifleBulletFactory::createObject()
{
    auto bullet = std::make_shared<Bullet>(
        ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_bullet), tileSize * 18.f, 22, Team::neutral);
    return bullet;
}

std::shared_ptr<GameObject> ShotgunBulletFactory::createObject()
{
    auto bullet = std::make_shared<Bullet>(
        ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_bullet), tileSize * 14.f, 14, Team::neutral);
    return bullet;
}
