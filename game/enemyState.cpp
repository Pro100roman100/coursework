#include "enemyState.h"
#include "enemy.h"
#include "player.h"
#include <cmath>

void PatrolState::enter(Enemy* enemy)
{
}

void PatrolState::update(Enemy* enemy, float deltaTime)
{
    if (enemy->canSeePlayer())
    {
        enemy->changeState(std::make_shared<CombatState>());
        return;
    }

    const auto& patrolPoints = enemy->getPatrolPoints();
    if (patrolPoints.empty())
        return;

    size_t currentIndex = enemy->getCurrentPatrolIndex();
    sf::Vector2f currentTarget = patrolPoints[currentIndex];
    sf::Vector2f directionToTarget = currentTarget - enemy->getPosition();
    float distanceToTarget = std::sqrt(directionToTarget.x * directionToTarget.x + 
                                       directionToTarget.y * directionToTarget.y);

    if (distanceToTarget < 1.f)
    {
        enemy->changeState(std::make_shared<IdleState>());
    }
    else
    {
        enemy->moveCharacter(directionToTarget, deltaTime);
        enemy->updateDirection(directionToTarget);
    }
}

void PatrolState::exit(Enemy* enemy)
{
}

void CombatState::enter(Enemy* enemy)
{
    lostSightTimer = 0.f;
    attackTimer = attackPause;
}

void CombatState::update(Enemy* enemy, float deltaTime)
{
    Player* target = Player::getActive();
    if (!target) 
        return;

    sf::Vector2f direction = target->getPosition() - enemy->getPosition();
    enemy->updateDirection(direction);
    enemy->setAttackDirection(direction);

    float distance = sqrt((direction.x) * (direction.x) + (direction.y) * (direction.y));
    bool hasLineOfSight = PhysicsManager::getInstance().checkPath(enemy->getPosition(), target->getPosition());

    if (!hasLineOfSight && lostSightTimer <= 0) {
        enemy->changeState(std::make_shared<PatrolState>());
        return;
    }

    if (distance > getAttackRange(enemy)) {
        enemy->moveCharacter(direction, deltaTime);
    }
    if (hasLineOfSight) {
        lostSightTimer = lostSightThreshold;
        if (attackTimer <= 0.f) {
            enemy->attack();
            enemy->getInventory().addAmmo(enemy->getInventory().getCurrentWeapon()->getType(), 1);
        }
        else
            attackTimer -= deltaTime;
    }
    else {
        attackTimer = attackPause;
        if (lostSightTimer > 0)
            lostSightTimer -= deltaTime;
    }
}

void CombatState::exit(Enemy* enemy)
{
}

float CombatState::getAttackRange(Enemy* enemy) const
{
    WeaponType weapon = enemy->getInventory().getCurrentWeapon()->getType();
    switch (weapon)
    {
    case WeaponType::Knife:
        return knifeAttackRange;
    case WeaponType::Shotgun:
        return attackRange / 2.f;
    default:
        return attackRange;
    }
}

void IdleState::enter(Enemy* enemy)
{
    stopTimer = checkpointStopTime;
}

void IdleState::update(Enemy* enemy, float deltaTime)
{
    stopTimer -= deltaTime;

    if (stopTimer <= 0.f)
    {
        enemy->advancePatrolIndex();
        enemy->changeState(std::make_shared<PatrolState>());
    }
}

void IdleState::exit(Enemy* enemy)
{
}
