#include "gameObject.h"

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void GameObject::move(sf::Vector2f transform)
{
	setPosition(getPosition() + transform);
}

sf::Vector2f GameObject::getPosition() const
{
	return sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void GameObject::onCollision(PhysicsObject* target)
{
	// Default implementation - do nothing
}
