#pragma once

#include "character.h"
#include "game.h"

#include "knife.h"
#include "pistol.h"
#include "rifle.h"
#include "shotgun.h"

class Enemy : public Character
{
public:
	Enemy(sf::Texture& texture);
	~Enemy();

	void update(float deltaTime) override;
	Team getTeam() override;
};

class KnifeEnemyFactory : public ObjectFactory
{
public:
	KnifeEnemyFactory() = delete;
	static std::shared_ptr<GameObject> createObject();
};

class PistolEnemyFactory : public ObjectFactory
{
public:
	PistolEnemyFactory() = delete;
	static std::shared_ptr<GameObject> createObject();
};

class RifleEnemyFactory : public ObjectFactory
{
public:
	RifleEnemyFactory() = delete;
	static std::shared_ptr<GameObject> createObject();
};

class ShotgunEnemyFactory : public ObjectFactory
{
public:
	ShotgunEnemyFactory() = delete;
	static std::shared_ptr<GameObject> createObject();
};

