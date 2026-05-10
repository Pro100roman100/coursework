#include "knife.h"
#include "physicsManager.h"
#include "character.h"

Knife::Knife(Character* owner) : Weapon(ResourceManager::getInstance().getTexture(ResourceManager::Texture::knife), owner)
{
    setCooldown(.4f);
}

void Knife::attack(sf::Vector2f direction)
{
    int damage = 50;

    sf::Vector2f hitCenter = getPosition() + (direction * (tileSize / 2.6f));
    CircleCollider hitArea(hitCenter, tileSize / 2.f);

    std::vector<PhysicsObject*> overlaps = PhysicsManager::getInstance().checkOverlap(hitArea);

    for (PhysicsObject* obj : overlaps) {
        if (Damageable* damageable = dynamic_cast<Damageable*>(obj)) {
            if (damageable->getTeam() != owner->getTeam()) {
                damageable->takeDamage(damage);
                return;
            }
        }
    }
}

WeaponType Knife::getType() const
{
    return WeaponType::Knife;
}

int Knife::getStartAmmo() const
{
    return 0;
}
