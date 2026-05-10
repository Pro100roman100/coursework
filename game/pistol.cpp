#include "pistol.h"
#include "physicsManager.h"
#include "objectManager.h"
#include "character.h"

Pistol::Pistol(Character* owner) : Weapon(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol), owner)
{
    setCooldown(.4f);
}

void Pistol::attack(sf::Vector2f direction)
{
    if (owner->getInventory().getAmmo(getType()) <= 0)
        return;

    owner->getInventory().useAmmo(getType(), 1);
    auto bulletObj = ObjectManager::getInstance().addObject<PistolBulletFactory>();
    if (Bullet* bullet = dynamic_cast<Bullet*>(bulletObj.get())) {
        bullet->setPosition(getPosition());
        bullet->setOwnerTeam(owner->getTeam());
        bullet->setVelocity(direction);
    }
    else
        std::cout << "Incorect bullet" << std::endl;
}

WeaponType Pistol::getType() const
{
    return WeaponType::Pistol;
}

int Pistol::getStartAmmo() const
{
    return 16;
}
