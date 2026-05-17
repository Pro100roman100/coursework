#include "factory.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "tile.h"
#include "dummy.h"
#include "weaponItem.h"
#include "bulletItem.h"
#include "healItem.h"
#include "resourceManager.h"
#include "knife.h"
#include "pistol.h"
#include "rifle.h"
#include "shotgun.h"
#include "effect.h"

namespace Factory
{
    std::shared_ptr<GameObject> createPistolBullet()
    {
        auto bullet = std::make_shared<Bullet>(
            ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_bullet), tileSize * 15.f, 6, Team::neutral);
        return bullet;
    }

    std::shared_ptr<GameObject> createRifleBullet()
    {
        auto bullet = std::make_shared<Bullet>(
            ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_bullet), tileSize * 18.f, 3, Team::neutral);
        return bullet;
    }

    std::shared_ptr<GameObject> createShotgunBullet()
    {
        auto bullet = std::make_shared<Bullet>(
            ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_bullet), tileSize * 14.f, 3, Team::neutral);
        return bullet;
    }

    std::shared_ptr<GameObject> createKnifeEnemy()
    {
        auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
        enemy->addWeapon(std::make_shared<Knife>(enemy.get()));
        return enemy;
    }

    std::shared_ptr<GameObject> createPistolEnemy()
    {
        auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
        enemy->addWeapon(std::make_shared<Pistol>(enemy.get()));
        return enemy;
    }

    std::shared_ptr<GameObject> createRifleEnemy()
    {
        auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
        enemy->addWeapon(std::make_shared<Rifle>(enemy.get()));
        return enemy;
    }

    std::shared_ptr<GameObject> createShotgunEnemy()
    {
        auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
        enemy->addWeapon(std::make_shared<Shotgun>(enemy.get()));
        return enemy;
    }

    std::shared_ptr<GameObject> createPlayer()
    {
        auto player = std::make_shared<Player>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::player));
        player->setPosition(sf::Vector2f(0.f, 0.f));
        return player;
    }

    std::shared_ptr<GameObject> createTile()
    {
        return std::make_shared<Tile>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::tile));
    }

    std::shared_ptr<GameObject> createDummy()
    {
        auto dummy = std::make_shared<Dummy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::player));
        return dummy;
    }

    std::shared_ptr<GameObject> createKnifeItem()
    {
        auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::knife_item),
            std::make_shared<Knife>(nullptr));
        item->setPosition(sf::Vector2f(0.f, 0.f));
        return item;
    }

    std::shared_ptr<GameObject> createPistolItem()
    {
        auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_item),
            std::make_shared<Pistol>(nullptr));
        item->setPosition(sf::Vector2f(0.f, 0.f));
        return item;
    }

    std::shared_ptr<GameObject> createRifleItem()
    {
        auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_item),
            std::make_shared<Rifle>(nullptr));
        item->setPosition(sf::Vector2f(0.f, 0.f));
        return item;
    }

    std::shared_ptr<GameObject> createShotgunItem()
    {
        auto item = std::make_shared<WeaponItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_item),
            std::make_shared<Shotgun>(nullptr));
        item->setPosition(sf::Vector2f(0.f, 0.f));
        return item;
    }

    std::shared_ptr<GameObject> createPistolAmmoItem()
    {
        auto item = std::make_shared<BulletItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_bullet_item),
            WeaponType::Pistol, 16);
        return item;
    }

    std::shared_ptr<GameObject> createRifleAmmoItem()
    {
        auto item = std::make_shared<BulletItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_bullet_item),
            WeaponType::Rifle, 45);
        return item;
    }

    std::shared_ptr<GameObject> createShotgunAmmoItem()
    {
        auto item = std::make_shared<BulletItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_bullet_item),
            WeaponType::Shotgun, 9);
        return item;
    }

    std::shared_ptr<GameObject> createHealItem()
    {
        auto item = std::make_shared<HealItem>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::heal_item), 50);
        return item;
    }
    
    std::shared_ptr<GameObject> createKnifeEffect()
    {
        auto item = std::make_shared<Effect>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::knife_effect));
        return item;
    }
}
