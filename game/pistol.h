#pragma once

#include "weapon.h"
#include "bullet.h"
#include "resourceManager.h"

class Pistol : public Weapon
{
public:

    Pistol(Character* owner);
    void attack(sf::Vector2f direction) override;
    WeaponType getType() const override;
    int getStartAmmo() const override;
};
