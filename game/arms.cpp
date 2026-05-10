#include "arms.h"
#include "character.h"

Arms::Arms(Character* owner) : Weapon(ResourceManager::getInstance().getTexture(ResourceManager::Texture::arms), owner)
{
}

void Arms::attack(sf::Vector2f direction)
{

}

WeaponType Arms::getType() const
{
    return WeaponType::Knife;
}

int Arms::getStartAmmo() const
{
    return 0;
}
