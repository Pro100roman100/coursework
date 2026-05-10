#include "character.h"
#include "objectManager.h"

Character::Character(const sf::Texture& texture) : GameObject(texture)
{
    updateSpriteRect();
    sprite.setOrigin(sprite.getLocalBounds().size / 2.f);
}

int Character::getHealth() const
{
    return health;
}

void Character::addWeapon(std::shared_ptr<Weapon> weapon)
{
    inventory.addWeapon(weapon);
    setCurentWeapon(inventory.getCurrentWeapon());
}

InventoryManager& Character::getInventory()
{
    return inventory;
}

bool Character::switchWeapon(int index)
{
    if (!inventory.switchWeapon(index))
        return false;

    setCurentWeapon(inventory.getCurrentWeapon());
    return true;
}

void Character::attack() {
   if (currentWeapon)
        currentWeapon->weaponAttack(attackDirection);
}
void Character::setCurentWeapon(std::shared_ptr<Weapon> weapon) {
    currentWeapon = weapon;
  if (!currentWeapon)
        return;

    currentWeapon->setPosition(getPosition());
    currentWeapon->setDirection(currentDirection);
}

void Character::setDirection(Direction dir)
{
    currentDirection = dir;
    updateSpriteRect();
}
void Character::moveCharacter(const sf::Vector2f& direction, float deltaTime) {
    if (direction == sf::Vector2f(0.f, 0.f))
        return;

    move(direction.normalized() * speed * deltaTime);
}

void Character::setAttackDirection(const sf::Vector2f& direction)
{
    if (direction != sf::Vector2f())
        attackDirection = direction.normalized();
}

sf::Vector2f Character::getAttackDirection() const
{
    return attackDirection;
}

void Character::updateSpriteRect()
{   
    sprite.setTextureRect(sf::IntRect({currentDirection * tileSize, 0}, { tileSize, tileSize }));
    if (currentWeapon)
        currentWeapon->setDirection(currentDirection);
}

void Character::setPosition(sf::Vector2f position)
{
    GameObject::setPosition(position);
    if (currentWeapon)
        currentWeapon->setPosition(position);
}

void Character::takeDamage(int damage)
{
    if (damage < 0)
        return;

    health -= damage;

    isFlashing = true;
    flashClock.restart();

    if (health <= 0)
    {
        ObjectManager::getInstance().removeObject(this);
    }
}

void Character::heal(int heal)
{
    if (heal < 0)
        return;

    health += heal;
    if (health > maxHealth)
        health = maxHealth;
}

void Character::updateFlash() const
{
    if (isFlashing && flashClock.getElapsedTime() >= flashDuration)
        isFlashing = false;
}

void Character::updateDirection(const sf::Vector2f& direction)
{
    if (abs(direction.x) > abs(direction.y)) {
        setDirection(direction.x > 0 ? Direction::Right : Direction::Left);
    }
    else {
        setDirection(direction.y > 0 ? Direction::Down : Direction::Up);
    }
}

Collider Character::getCollider() const
{
    return CircleCollider(getPosition(), tileSize / 2);
}

PhysicsObject::ObjectType Character::getType() const
{
    return PhysicsObject::ObjectType::_dynamic_;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    updateFlash(); 
    
    if (isFlashing)
    {
        target.draw(sprite);

        sf::RenderStates additiveStates = states;
        additiveStates.blendMode = sf::BlendAdd;
        target.draw(sprite, additiveStates);
    }
    else
    {
        target.draw(sprite, states);
    }

    if (currentWeapon)
        target.draw(*currentWeapon, states);
}