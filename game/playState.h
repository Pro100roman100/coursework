#pragma once

#include "gameState.h"
#include "fileManager.h"
#include "image.h"
#include "text.h"

class PlayState : public GameState {
private:
    void initUI();

public:

    PlayState();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow* window) override;
    void ui(sf::RenderWindow* window) override;
    void restart() override;
};