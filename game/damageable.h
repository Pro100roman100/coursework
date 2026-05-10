#pragma once

enum class Team {
    player,
    enemy,
    neutral
};

__interface Damageable
{
public:
    virtual void takeDamage(int damage) = 0;
    virtual void heal(int heal) = 0;
    virtual int getHealth() const = 0;
    virtual Team getTeam() = 0;
};