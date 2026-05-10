#pragma once
#include "character.h"
#include "arms.h"
#include "resourceManager.h"
#include "objectManager.h"
#include "game.h"

class Dummy : public Character
{
public:
    Dummy(const sf::Texture& texture) : Character(texture) {
      setCurentWeapon(std::make_shared<Arms>(this));
        Game::getInstance().incrementEnemyCount();
    }
    ~Dummy() {
        Game::getInstance().decrementEnemyCount();
    }

    void update(float deltaTime) override { }
    Team getTeam() override;
};

class DummyFactory : public ObjectFactory
{
public:
    static std::shared_ptr<GameObject> createObject()
    {
        auto dummy = std::make_shared<Dummy>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::player));
        return dummy;
    }
};