#include "bulletItem.h"

void BulletItem::onCollision(PhysicsObject* target)
{
	if (auto* player = dynamic_cast<Player*>(target)) {
		player->getInventory().addAmmo(type, ammoCount);
		ObjectManager::getInstance().removeObject(this);
	}
}

std::shared_ptr<GameObject> PistolAmmoItemFactory::createObject()
{
	auto item = std::make_shared<BulletItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_bullet_item),
		WeaponType::Pistol, 16);
	return item;
}

std::shared_ptr<GameObject> RifleAmmoItemFactory::createObject()
{
	auto item = std::make_shared<BulletItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_bullet_item),
		WeaponType::Rifle, 45);
	return item;
}

std::shared_ptr<GameObject> ShotgunAmmoItemFactory::createObject()
{
	auto item = std::make_shared<BulletItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_bullet_item),
		WeaponType::Shotgun, 9);
	return item;
}
