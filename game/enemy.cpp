#include "enemy.h"

#include "resourceManager.h"
#include "player.h"
#include "physicsManager.h"
#include "weaponType.h"
#include <cmath>

Enemy::Enemy(sf::Texture& texture) : Character(texture)
{
    maxHealth = 20;
    health = maxHealth;
    speed = enemySpeed;
    Game::getInstance().incrementEnemyCount();

    currentState = std::make_shared<PatrolState>();
    currentState->enter(this);
}

Enemy::~Enemy()
{
    Game::getInstance().decrementEnemyCount();
}

void Enemy::update(float deltaTime)
{
    if (currentState)
    {
        currentState->update(this, deltaTime);
    }
}

Team Enemy::getTeam()
{
    return Team::enemy;
}

bool Enemy::canSeePlayer() const
{
    Player* player = Player::getActive();
    if (!player)
        return false;

    sf::Vector2f directionToPlayer = player->getPosition() - getPosition();
    float distanceToPlayer = std::sqrt(directionToPlayer.x * directionToPlayer.x + 
                                       directionToPlayer.y * directionToPlayer.y);
    
    if (distanceToPlayer > sightRange)
        return false;

    return canSeePlayerWithRaycast();
}

bool Enemy::canSeePlayerWithRaycast() const
{
    Player* player = Player::getActive();
    if (!player)
        return false;

    sf::Vector2f rayStart = getPosition();
    sf::Vector2f rayEnd = player->getPosition();

    bool pathClear = PhysicsManager::getInstance().checkPath(rayStart, rayEnd);

    return pathClear;
}

void Enemy::changeState(std::shared_ptr<IEnemyState> newState)
{
    if (currentState)
    {
        currentState->exit(this);
    }

    currentState = newState;

    if (currentState)
    {
        currentState->enter(this);
    }
}

void Enemy::takeDamage(int damage)
{
    if(!dynamic_cast<CombatState*>(currentState.get()))
        changeState(std::make_shared<CombatState>());
    Character::takeDamage(damage);
}

void Enemy::addPatrolPoint(sf::Vector2f point)
{
    patrolPoints.push_back(point);
}

void Enemy::setPatrolPoints(const std::vector<sf::Vector2f>& points)
{
    patrolPoints = points;
    currentPatrolIndex = 0;
    if (!patrolPoints.empty())
    {
        setPosition(patrolPoints[0]);
    }
}
