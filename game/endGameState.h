#pragma once

#include "gameState.h"

class EndGameState : public GameState
{
public:
	EndGameState();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow* window) override;
	void ui(sf::RenderWindow* window) override;
	void restart() override;
	void escape() override;
};

