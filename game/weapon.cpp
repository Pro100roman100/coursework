#include "weapon.h"

Weapon::Weapon(sf::Texture& texture, Character* owner) : sprite(texture), owner(owner)
{
	setTextureRect();
	sprite.setOrigin(sprite.getLocalBounds().size / 2.f);
	attackTimer.start();
}

bool Weapon::canAttack()
{
	return attackTimer.getElapsedTime().asSeconds() > attackCooldown;
}

void Weapon::setCooldown(float cooldown)
{
	attackCooldown = cooldown;
}

void Weapon::resetCooldown()
{
	attackTimer.restart();
}

void Weapon::setTextureRect()
{
	sprite.setTextureRect(sf::IntRect({ direction * tileSize, 0 }, { tileSize, tileSize }));
}

void Weapon::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

sf::Vector2f Weapon::getPosition() const
{
	return sprite.getPosition();
}

void Weapon::setDirection(Direction direction)
{
	this->direction = direction;
	setTextureRect();
}

void Weapon::weaponAttack(sf::Vector2f direction)
{
	if (canAttack()) {
		resetCooldown();
		attack(direction);
	}
}

void Weapon::setOwner(Character* newOwner)
{
	owner = newOwner;
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}