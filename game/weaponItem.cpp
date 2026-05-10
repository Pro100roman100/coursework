#include "weaponItem.h"
#include "pistol.h"
#include "rifle.h"
#include "shotgun.h"
#include "objectManager.h"

void WeaponItem::onCollision(PhysicsObject* target)
{
	if (auto* player = dynamic_cast<Player*>(target)) {
		weapon->setOwner(player);
		player->addWeapon(weapon);
		ObjectManager::getInstance().removeObject(this);
	}
}

std::shared_ptr<GameObject> KnifeItemFactory::createObject() {
	auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_item),
		std::make_shared<Knife>(nullptr));
	item->setPosition(sf::Vector2f(0.f, 0.f));
	return item;
}

std::shared_ptr<GameObject> PistolItemFactory::createObject() {
	auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_item),
		std::make_shared<Pistol>(nullptr));
	item->setPosition(sf::Vector2f(0.f, 0.f));
	return item;
}

std::shared_ptr<GameObject> RifleItemFactory::createObject() {
	auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_item),
		std::make_shared<Rifle>(nullptr));
	item->setPosition(sf::Vector2f(0.f, 0.f));
	return item;
}

std::shared_ptr<GameObject> ShotgunItemFactory::createObject() {
	auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_item),
		std::make_shared<Shotgun>(nullptr));
	item->setPosition(sf::Vector2f(0.f, 0.f));
	return item;
}