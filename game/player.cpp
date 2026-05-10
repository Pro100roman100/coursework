#include "player.h"

#include "resourceManager.h"
#include "consts.h"
#include "arms.h"
#include "camera.h"
#include "inputManager.h"

Player* Player::active = nullptr;

Player::Player(const sf::Texture& texture) : Character(texture)
{
    maxHealth = maxHealth * globalData::difficultyMultiplier;
    health = maxHealth;

    if (active != nullptr)
        std::cout << "Player allready exists!" << std::endl;
    active = this;

    addWeapon(std::make_shared<Knife>(this));
}
Player::~Player()
{
    active = nullptr;
}

void Player::update(float deltaTime)
{
    InputManager& input = InputManager::getInstance();

    sf::Vector2f movement = input.getMovementDirection();

    moveCharacter(movement, deltaTime);

    sf::Vector2f attackDir = sf::Vector2f();
    sf::Vector2f cursorWorldPos = input.getMouseWorldPosition();

    attackDir = cursorWorldPos - getPosition();

    shootTimer -= deltaTime;
    if (shootTimer <= 0) {
        if (movement != sf::Vector2f())
            updateDirection(movement);
    }
    else
        updateDirection(attackDir);

    setAttackDirection(attackDir);

    if (input.isAttacking()) {
        attack();
        shootTimer = shootCooldown;
    }

    int weaponIndex = input.getWeaponSelection();
    if (weaponIndex >= 0 && weaponIndex < static_cast<int>(inventory.getWeapons().size()))
        switchWeapon(weaponIndex);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
        takeDamage(1000000);
}

Team Player::getTeam()
{
    return Team::player;
}

Player* Player::getActive()
{
    return active;
}

std::shared_ptr<GameObject> PlayerFactory::createObject()
{
    auto player = std::make_shared<Player>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::player));
    player->setPosition(sf::Vector2f(0.f, 0.f));
    return player;
}
