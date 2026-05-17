#include "endGameState.h"

#include "game.h"
#include "text.h"
#include "button.h"
#include "menuState.h"

EndGameState::EndGameState() {
	uiManager->clear();

	auto text = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	switch (globalData::endState)
	{
	case globalData::lose:
		text->setText("You lost!");
		break;
	case globalData::win:
		FileManager::addCompletedMap(globalData::currentMap);
		text->setText("You won!");
		break;
	default:
		text->setText("Unknown state");
		break;
	}
	text->setOrigin({ .5f, .5f });
	text->setPosition(windowSize / 2.f);
	text->setFontSize(118.f);
	uiManager->addElement(text);

	auto restartButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	restartButton->setText("restart");
	restartButton->setFontSize(72.f);
	restartButton->setOrigin({ .5f, .5f });
	restartButton->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 160.f });
	restartButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	restartButton->setOnClick([]() {
		Game::getInstance().restart();
		});
	uiManager->addElement(restartButton);

	auto menuButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	menuButton->setText("main menu");
	menuButton->setFontSize(72.f);
	menuButton->setOrigin({ .5f, .5f });
	menuButton->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 240.f });
	menuButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	menuButton->setOnClick([]() {
		Game::getInstance().changeState(std::make_shared<MenuState>());
		});
	uiManager->addElement(menuButton);
}

void EndGameState::update(float deltaTime)
{
	uiManager->updateAll(deltaTime);
}

void EndGameState::draw(sf::RenderWindow* window)
{
	ObjectManager::getInstance().drawAll(window);
}

void EndGameState::ui(sf::RenderWindow* window)
{
	uiManager->drawAll(window);
}

void EndGameState::restart()
{
	Game::getInstance().changeState(std::make_shared<PlayState>());
}

void EndGameState::escape()
{
	Game::getInstance().changeState(std::make_shared<MenuState>());
}
