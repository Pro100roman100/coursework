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
