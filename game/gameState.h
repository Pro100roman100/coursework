#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "objectManager.h"
#include "physicsManager.h"
#include "uiManager.h"
#include "resourceManager.h"
#include "globalData.h"

class GameState {
protected:
    std::shared_ptr<UiManager> uiManager;

    GameState() : uiManager(std::make_shared<UiManager>()) {}

public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void ui(sf::RenderWindow* window) = 0;
    virtual void restart() = 0;
    virtual void handleClick(const sf::Vector2f& clickPos) { uiManager->handleClick(clickPos); }
    virtual void escape() = 0;

    UiManager& getUiManager() const { return *uiManager; }
};