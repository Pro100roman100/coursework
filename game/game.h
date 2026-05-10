#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "singleton.h"
#include "resourceManager.h"
#include "gameState.h"
#include "playState.h"
#include "menuState.h"
#include "levelSelectState.h"
#include "settingsState.h"
#include "consts.h"
#include "camera.h"

class Game : public Singleton<Game>
{
	friend class Singleton<Game>;

private:

	Game() = default;

	sf::RenderWindow* window = nullptr;

	sf::View uiCamera;
	Camera defaultCamera;

	std::shared_ptr<GameState> currentState = nullptr;

	float deltaTime = 1 / 60.f;
	bool FPSToggle = false;
	bool collidersToggle = false;
	bool coordinatesToggle = false;
	void displayFPS();
	void displayCoordinates();

	int enemyCount = 0;

public:
	void init(sf::RenderWindow* window);
	void restart();
	void toggleFPS();
	void toggleColliders();
	void toggleCoordinates();
	void mousePress(const sf::Event::MouseButtonPressed& mousePressed);
	void update();
	void cleanup();

	void incrementEnemyCount();
	void decrementEnemyCount();
	int getEnemyCount();

	void changeState(std::shared_ptr<GameState> newState);
};