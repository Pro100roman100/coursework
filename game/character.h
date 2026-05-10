#pragma once

#include "consts.h"
#include "damageable.h"
#include "gameObject.h"
#include "inventoryManager.h"
#include "weapon.h"

class Character : public GameObject, public Damageable
{
private:
    Direction currentDirection = Down;
    sf::Vector2f attackDirection = {};

    sf::Clock flashClock;
    const sf::Time flashDuration = sf::seconds(0.15f);

protected:
    std::shared_ptr<Weapon> currentWeapon;
    InventoryManager inventory;
    float speed = 50.f;
    int maxHealth = 100;
    int health = maxHealth;

    mutable bool isFlashing = false;

    Character(const sf::Texture& texture);

    void attack();
    void setCurentWeapon(std::shared_ptr<Weapon> weapon);

    void setAttackDirection(const sf::Vector2f& direction);
    sf::Vector2f getAttackDirection() const;

    void updateFlash() const;
    void moveCharacter(const sf::Vector2f& direction, float deltaTime);
    void updateDirection(const sf::Vector2f& direction);

private:
    void updateSpriteRect();
    void setDirection(Direction dir);

public:
    void setPosition(sf::Vector2f position) override;

    void addWeapon(std::shared_ptr<Weapon> weapon);
    InventoryManager& getInventory();
    bool switchWeapon(int index);

    void update(float deltaTime) override = 0;
    Collider getCollider() const override;
    PhysicsObject::ObjectType getType() const override;

    Team getTeam() override = 0;
    void takeDamage(int damage) override;
    void heal(int heal) override;
    int getHealth() const override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};