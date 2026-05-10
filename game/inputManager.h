#pragma once

#include <SFML/Graphics.hpp>
#include "singleton.h"
#include "camera.h"

class InputManager : public Singleton<InputManager>
{
    friend class Singleton<InputManager>;

private:
    InputManager() = default;

    bool getMovementKey(sf::Keyboard::Key key1, sf::Keyboard::Key key2) const;
    sf::RenderWindow* window = nullptr;

public:

    void setWindow(sf::RenderWindow* window);

    sf::Vector2f getMovementDirection() const;
    bool isAttacking() const;
    int getWeaponSelection() const;

    sf::Vector2f getMouseWorldPosition() const;
    sf::Vector2i getMouseScreenPosition() const;
};
