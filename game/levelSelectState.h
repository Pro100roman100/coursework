#pragma once

#include "gameState.h"
#include "button.h"
#include "text.h"

class LevelSelectState : public GameState
{
public:
    LevelSelectState();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow* window) override;
    void ui(sf::RenderWindow* window) override;
    void restart() override;
};
