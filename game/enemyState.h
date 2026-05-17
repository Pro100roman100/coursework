#pragma once

#include <memory>

class Enemy;

class IEnemyState
{
public:
    virtual ~IEnemyState() = default;

    virtual void enter(Enemy* enemy) {}
    virtual void update(Enemy* enemy, float deltaTime) = 0;
    virtual void exit(Enemy* enemy) {}
};

class PatrolState : public IEnemyState
{
public:
    void enter(Enemy* enemy) override;
    void update(Enemy* enemy, float deltaTime) override;
    void exit(Enemy* enemy) override;
};

class IdleState : public IEnemyState
{
private:
    const float checkpointStopTime = 0.6f;
    float stopTimer = 0.f;

public:
    void enter(Enemy* enemy) override;
    void update(Enemy* enemy, float deltaTime) override;
    void exit(Enemy* enemy) override;
};

class CombatState : public IEnemyState
{
private:
    float lostSightTimer = 0.f;
    const float lostSightThreshold = 1.5f;

    float attackTimer = 0.f;
    const float attackPause = .5f;

    const float attackRange = 16.f * 5.f;
    const float knifeAttackRange = 16.f;  

public:
    void enter(Enemy* enemy) override;
    void update(Enemy* enemy, float deltaTime) override;
    void exit(Enemy* enemy) override;

    float getAttackRange(Enemy* enemy) const;
};