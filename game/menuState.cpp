#include "menuState.h"

#include "game.h"
#include "settingsState.h"

MenuState::MenuState()
{
	UiManager::getInstance().clear();

	auto playButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	playButton->setText("play");
	playButton->setFontSize(96.f);
	playButton->setOrigin({ .5f, .5f });
  playButton->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f - 60.f });
	playButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	playButton->setOnClick([]() {
     Game::getInstance().changeState(std::make_shared<LevelSelectState>());
		});
	UiManager::getInstance().addElement(playButton);

	auto settingsButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	settingsButton->setText("settings");
	settingsButton->setFontSize(96.f);
	settingsButton->setOrigin({ .5f, .5f });
	settingsButton->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 60.f });
	settingsButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	settingsButton->setOnClick([]() {
		Game::getInstance().changeState(std::make_shared<SettingsState>());
		});
	UiManager::getInstance().addElement(settingsButton);
}

void MenuState::update(float deltaTime)
{
	UiManager::getInstance().updateAll(deltaTime);
}

void MenuState::draw(sf::RenderWindow* window)
{
}

void MenuState::ui(sf::RenderWindow* window)
{
	UiManager::getInstance().drawAll(window);
}

void MenuState::restart()
{
}
