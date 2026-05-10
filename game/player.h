#pragma once

#include "character.h"
#include "knife.h"
#include "globalData.h"

class Player : public Character
{
private:
    float shootTimer = 0.f; // giving player shooting direction or movement direction
    const float shootCooldown = 1.5f;

    static Player* active;

public:

    Player(const sf::Texture& texture);
    ~Player();
    Team getTeam() override;

    void update(float deltaTime) override;

    static Player* getActive();
};

class PlayerFactory : public ObjectFactory {
public:
    static std::shared_ptr<GameObject> createObject();
};