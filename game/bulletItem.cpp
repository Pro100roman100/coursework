#include "bulletItem.h"

void BulletItem::onCollision(PhysicsObject* target)
{
	if (auto* player = dynamic_cast<Player*>(target)) {
		player->getInventory().addAmmo(type, ammoCount);
		ObjectManager::getInstance().removeObject(this);
	}
}
