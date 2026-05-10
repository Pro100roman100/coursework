#pragma once

#include "gameState.h"
#include "button.h"

class MenuState : public GameState
{
public:
	MenuState();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow* window) override;
	void ui(sf::RenderWindow* window) override;
	void restart() override;
};

