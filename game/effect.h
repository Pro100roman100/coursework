#pragma once

#include "gameObject.h"

class Effect : public GameObject
{
private:
	float lifeSpan = 1.f;

public:

	Effect(sf::Texture& texture);
	void setLifespan(float lifespan);

	void setRotation(sf::Angle rotation);

	void update(float deltaTime) override;
	Collider getCollider() const override;
	PhysicsObject::ObjectType getType() const override;
};

