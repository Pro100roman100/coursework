#pragma once

#include "item.h"
#include "player.h"
#include "resourceManager.h"

class WeaponItem : public Item
{
private:

	std::shared_ptr<Weapon> weapon;

public:

	WeaponItem(sf::Texture& texture, std::shared_ptr<Weapon> weapon) : Item(texture)
	{
		this->weapon = weapon;
	}
	void onCollision(PhysicsObject* target) override;
};
