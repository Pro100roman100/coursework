#include "rifle.h"
#include "factory.h"
#include "physicsManager.h"
#include "objectManager.h"
#include "character.h"

Rifle::Rifle(Character* owner) : Weapon(ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle), owner)
{
    setCooldown(0.11f);
}

void Rifle::attack(sf::Vector2f direction)
{
    if (owner->getInventory().getAmmo(getType()) <= 0)
        return;

    owner->getInventory().useAmmo(getType(), 1);
    auto bulletObj = ObjectManager::getInstance().addObject(Factory::createRifleBullet());
    if (Bullet* bullet = dynamic_cast<Bullet*>(bulletObj.get())) {
        bullet->setPosition(getPosition());
        bullet->setOwnerTeam(owner->getTeam());

        float spread = (rand() / (float)RAND_MAX - 0.5f) * 0.2f;
        float angle = std::atan2(direction.y, direction.x) + spread;
        float speed = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f spreadDirection(std::cos(angle) * speed, std::sin(angle) * speed);

        bullet->setVelocity(spreadDirection);
    }
    else
        std::cout << "Incorect bullet" << std::endl;
}

WeaponType Rifle::getType() const
{
    return WeaponType::Rifle;
}

int Rifle::getStartAmmo() const
{
    return 45;
}
