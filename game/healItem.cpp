#include "healItem.h"

void HealItem::onCollision(PhysicsObject* target)
{
    if (auto* player = dynamic_cast<Player*>(target)) {
        player->heal(healAmount * globalData::difficultyMultiplier);
        ObjectManager::getInstance().removeObject(this);
    }
}
