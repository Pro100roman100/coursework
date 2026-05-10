#include "shotgun.h"
#include "objectManager.h"
#include "physicsManager.h"
#include "character.h"
#include <cmath>

Shotgun::Shotgun(Character* owner) : Weapon(ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun), owner)
{
    setCooldown(0.9f);
}

void Shotgun::attack(sf::Vector2f direction)
{
    if (owner->getInventory().getAmmo(getType()) <= 0)
        return;

    owner->getInventory().useAmmo(getType(), 1);
    for (int i = 0; i < 8; i++)
    {
        auto bulletObj = ObjectManager::getInstance().addObject<ShotgunBulletFactory>();
        if (Bullet* bullet = dynamic_cast<Bullet*>(bulletObj.get())) {
            bullet->setPosition(getPosition());
            bullet->setOwnerTeam(owner->getTeam());

            float spread = (rand() / (float)RAND_MAX - 0.5f) * 0.45f;
            float angle = std::atan2(direction.y, direction.x) + spread;
            float speed = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            sf::Vector2f spreadDirection(std::cos(angle) * speed, std::sin(angle) * speed);

            bullet->setVelocity(spreadDirection);
        }
        else
            std::cout << "Incorect bullet" << std::endl;
    }
}

WeaponType Shotgun::getType() const
{
    return WeaponType::Shotgun;
}

int Shotgun::getStartAmmo() const
{
    return 9;
}
