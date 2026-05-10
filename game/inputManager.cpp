#include "inputManager.h"

void InputManager::setWindow(sf::RenderWindow* window)
{
    this->window = window;
}

bool InputManager::getMovementKey(sf::Keyboard::Key key1, sf::Keyboard::Key key2) const
{
    return sf::Keyboard::isKeyPressed(key1) || sf::Keyboard::isKeyPressed(key2);
}

sf::Vector2f InputManager::getMovementDirection() const
{
    sf::Vector2f direction(0.f, 0.f);

    if (getMovementKey(sf::Keyboard::Key::W, sf::Keyboard::Key::Up))
        direction.y -= 1;
    if (getMovementKey(sf::Keyboard::Key::S, sf::Keyboard::Key::Down))
        direction.y += 1;
    if (getMovementKey(sf::Keyboard::Key::A, sf::Keyboard::Key::Left))
        direction.x -= 1;
    if (getMovementKey(sf::Keyboard::Key::D, sf::Keyboard::Key::Right))
        direction.x += 1;

    return direction;
}

bool InputManager::isAttacking() const
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

int InputManager::getWeaponSelection() const
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
        return 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
        return 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
        return 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
        return 3;
    return -1;
}

sf::Vector2f InputManager::getMouseWorldPosition() const
{
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
    return window->mapPixelToCoords(mousePixel, Camera::getActive()->getView());
}

sf::Vector2i InputManager::getMouseScreenPosition() const
{
    return sf::Mouse::getPosition();
}