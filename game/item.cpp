#include "item.h"

void Item::update(float deltaTime)
{
}

Collider Item::getCollider() const
{
    return CircleCollider(getPosition(), tileSize / 3);
}

PhysicsObject::ObjectType Item::getType() const
{
    return PhysicsObject::ObjectType::_trigger_;
}