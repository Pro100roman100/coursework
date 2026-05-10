#pragma once

#include "gameObject.h"
#include "objectManager.h"
#include "consts.h"

class Item : public GameObject
{
protected:
	Item(sf::Texture& texture) : GameObject(texture) {}

public:
	void update(float deltaTime) override;
	Collider getCollider() const override;
	PhysicsObject::ObjectType getType() const override;
	void onCollision(PhysicsObject* target) override = 0;
};

