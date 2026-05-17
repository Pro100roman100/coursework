#pragma once

#include <SFML/Graphics.hpp>
#include "physicsObject.h"

class GameObject : public sf::Drawable, public PhysicsObject
{
protected:

	sf::Sprite sprite;

	GameObject(const sf::Texture& texture) : sprite(texture) {
		sprite.setOrigin(sprite.getLocalBounds().size / 2.f);
	}

public:

	sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f position);
	void move(sf::Vector2f transform) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(float deltaTime) = 0;

	Collider getCollider() const override = 0;
	PhysicsObject::ObjectType getType() const override = 0;
	void onCollision(PhysicsObject* target) override;
};
