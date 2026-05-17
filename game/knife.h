#pragma once

#include "weapon.h"
#include "resourceManager.h"
#include "effect.h"

class Knife : public Weapon
{
public:

    Knife(Character* owner);
    void attack(sf::Vector2f direction) override;
    WeaponType getType() const override;
    int getStartAmmo() const override;
};