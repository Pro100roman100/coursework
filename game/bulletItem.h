#pragma once

#include "item.h"
#include "player.h"

class BulletItem : public Item
{
private:
	WeaponType type;
	int ammoCount;

public:
	BulletItem(sf::Texture& texture, WeaponType type, int ammoCount) : Item(texture), type(type), ammoCount(ammoCount){}

	void onCollision(PhysicsObject* target) override;
};

class PistolAmmoItemFactory : public ObjectFactory {
public:
	PistolAmmoItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};
class RifleAmmoItemFactory : public ObjectFactory {
public:
	RifleAmmoItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};
class ShotgunAmmoItemFactory : public ObjectFactory {
public:
	ShotgunAmmoItemFactory() = delete;

	static std::shared_ptr<GameObject> createObject();
};
