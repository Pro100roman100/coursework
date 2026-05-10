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

class KnifeItemFactory : public ObjectFactory {
public:
	KnifeItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};

class PistolItemFactory : public ObjectFactory {
public:
	PistolItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};

class RifleItemFactory : public ObjectFactory {
public:
	RifleItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};

class ShotgunItemFactory : public ObjectFactory {
public:
	ShotgunItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};