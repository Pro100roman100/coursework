#include "knife.h"
#include "physicsManager.h"
#include "character.h"
#include "objectManager.h"
#include "factory.h"

Knife::Knife(Character* owner) : Weapon(ResourceManager::getInstance().getTexture(ResourceManager::Texture::knife), owner)
{
    setCooldown(.4f);
}

void Knife::attack(sf::Vector2f direction)
{
    int damage = 10;

    sf::Vector2f hitCenter = getPosition() + (direction * (tileSize / 2.6f));
    CircleCollider hitArea(hitCenter, tileSize / 2.f);

    std::vector<PhysicsObject*> overlaps = PhysicsManager::getInstance().checkOverlap(hitArea);

    auto obj = ObjectManager::getInstance().addObject(Factory::createKnifeEffect());
    if (auto* effect = dynamic_cast<Effect*>(obj.get())) {
        effect->setPosition(getPosition());
        effect->setRotation(direction.angle());
        effect->setLifespan(.06f);
    }

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
