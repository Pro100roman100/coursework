#pragma once

#include "character.h"
#include "game.h"

#include "knife.h"
#include "pistol.h"
#include "rifle.h"
#include "shotgun.h"
#include "enemyState.h"
#include <vector>
#include <memory>

class PatrolState;
class IdleState;
class CombatState;

class Enemy : public Character
{
	friend class PatrolState;
	friend class IdleState;
	friend class CombatState;

private:
	std::shared_ptr<IEnemyState> currentState;
	std::vector<sf::Vector2f> patrolPoints;
	size_t currentPatrolIndex = 0;

	const float enemySpeed = 40.f;
	const float sightRange = tileSize * 7.f;

	bool canSeePlayerWithRaycast() const;

public:
	Enemy(sf::Texture& texture);
	~Enemy();

	void update(float deltaTime) override;
	Team getTeam() override;

	void addPatrolPoint(sf::Vector2f point);
	void setPatrolPoints(const std::vector<sf::Vector2f>& points);

	void changeState(std::shared_ptr<IEnemyState> newState);
	void takeDamage(int damage) override;

	bool canSeePlayer() const;
	const std::vector<sf::Vector2f>& getPatrolPoints() const { return patrolPoints; }

	size_t getCurrentPatrolIndex() const { return currentPatrolIndex; }
	void setCurrentPatrolIndex(size_t index) { currentPatrolIndex = index; }
	void advancePatrolIndex() { currentPatrolIndex = (currentPatrolIndex + 1) % patrolPoints.size(); }
};
