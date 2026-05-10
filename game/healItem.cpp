#include "healItem.h"

void HealItem::onCollision(PhysicsObject* target)
{
    if (auto* player = dynamic_cast<Player*>(target)) {
        player->heal(healAmount * globalData::difficultyMultiplier);
        ObjectManager::getInstance().removeObject(this);
    }
}

std::shared_ptr<GameObject> HealItemFactory::createObject()
{
    auto item = std::make_shared<HealItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::heal_item), 35);
    return item;
}
