#pragma once

#include "gameState.h"
#include "fileManager.h"
#include "image.h"
#include "text.h"
#include "uiManager.h"

class PlayState : public GameState {
private:
    bool isPaused = false;
    std::shared_ptr<UiManager> pauseUiManager;

    void initUI();
    void initPauseMenu();

public:

    PlayState();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow* window) override;
    void ui(sf::RenderWindow* window) override;
    void restart() override;
    void handleClick(const sf::Vector2f& clickPos) override;
    void escape() override;
};