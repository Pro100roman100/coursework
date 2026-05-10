#pragma once

#include <SFML/Graphics.hpp>
#include "objectManager.h"
#include "physicsManager.h"
#include "uiManager.h"
#include "resourceManager.h"
#include "globalData.h"

class GameState {
protected:
    GameState() = default;

public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void ui(sf::RenderWindow* window) = 0;
    virtual void restart() = 0;
};