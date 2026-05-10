#pragma once

#include <SFML/Graphics.hpp>
#include "consts.h"
#include "weaponType.h"
#include "damageable.h"

class Character;

class Weapon : public sf::Drawable {
private:

	sf::Sprite sprite;
	Direction direction = Direction::Down;

	void setTextureRect();
	sf::Clock attackTimer;

protected:

	float attackCooldown = 1;
	Character* owner;
	Weapon(sf::Texture& texture, Character* owner);

	bool canAttack();
	void setCooldown(float cooldown);
	void resetCooldown();

	virtual void attack(sf::Vector2f direction) = 0;

public:

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	void setDirection(Direction direction);
	void weaponAttack(sf::Vector2f direction);
	void setOwner(Character* newOwner);

    virtual WeaponType getType() const = 0;
	virtual int getStartAmmo() const = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};