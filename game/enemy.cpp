#include "enemy.h"

#include "resourceManager.h"

Enemy::Enemy(sf::Texture& texture) : Character(texture)
{
    Game::getInstance().incrementEnemyCount();
}

Enemy::~Enemy()
{
    Game::getInstance().decrementEnemyCount();
}

void Enemy::update(float deltaTime)
{
}

Team Enemy::getTeam()
{
    return Team::enemy;
}

std::shared_ptr<GameObject> KnifeEnemyFactory::createObject()
{
    auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
   enemy->addWeapon(std::make_shared<Knife>(enemy.get()));
    return enemy;
}

std::shared_ptr<GameObject> PistolEnemyFactory::createObject()
{
    auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
  enemy->addWeapon(std::make_shared<Pistol>(enemy.get()));
    return enemy;
}

std::shared_ptr<GameObject> RifleEnemyFactory::createObject()
{
    auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
   enemy->addWeapon(std::make_shared<Rifle>(enemy.get()));
    return enemy;
}

std::shared_ptr<GameObject> ShotgunEnemyFactory::createObject()
{
    auto enemy = std::make_shared<Enemy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::enemy));
 enemy->addWeapon(std::make_shared<Shotgun>(enemy.get()));
    return enemy;
}
