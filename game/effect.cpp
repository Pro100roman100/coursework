#include "effect.h"
#include "objectManager.h"

Effect::Effect(sf::Texture& texture) : GameObject(texture)
{
}

void Effect::setLifespan(float lifespan)
{
    this->lifeSpan = lifespan;
}

void Effect::setRotation(sf::Angle rotation)
{
    sprite.setRotation(rotation);
}

void Effect::update(float deltaTime)
{
    lifeSpan -= deltaTime;
    if (lifeSpan < 0)
        ObjectManager::getInstance().removeObject(this);
}

Collider Effect::getCollider() const
{
    return CircleCollider({getPosition()}, {0});
}

PhysicsObject::ObjectType Effect::getType() const
{
    return PhysicsObject::ObjectType::_trigger_;
}
