#pragma once

#include "item.h"
#include "player.h"
#include "globalData.h"

class HealItem : public Item
{
private:
    int healAmount;

public:
    HealItem(sf::Texture& texture, int healAmount) : Item(texture), healAmount(healAmount) {}

    void onCollision(PhysicsObject* target) override;
};
