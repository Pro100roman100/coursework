#include "settingsState.h"

#include "game.h"
#include "globalData.h"
#include "menuState.h"

static void addDifficultyButton(const std::string& label, float difficultyMultiplier, sf::Vector2f position)
{
    auto button = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
    button->setText(label);
    button->setFontSize(72.f);
    button->setOrigin({ .5f, .5f });
    button->setPosition(position);
    button->setBackgroundColor(sf::Color(129, 98, 113, 255));
    button->setUpdate([button, difficultyMultiplier](float) {
        if (globalData::difficultyMultiplier == difficultyMultiplier)
            button->setBackgroundColor(sf::Color(195, 163, 138, 255));
        else
            button->setBackgroundColor(sf::Color(129, 98, 113, 255));
        });
    button->setOnClick([difficultyMultiplier]() {
        globalData::difficultyMultiplier = difficultyMultiplier;
        FileManager::saveData();
        });
    UiManager::getInstance().addElement(button);
}

SettingsState::SettingsState()
{
    UiManager::getInstance().clear();

    auto title = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
    title->setText("Settings");
    title->setOrigin({ .5f, .5f });
    title->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f - 240.f });
    title->setFontSize(96.f);
    UiManager::getInstance().addElement(title);

    addDifficultyButton("easy", 1.5f, { windowSize.x / 2.f, windowSize.y / 2.f - 80.f });
    addDifficultyButton("medium", 1.f, { windowSize.x / 2.f, windowSize.y / 2.f });
    addDifficultyButton("hard", 0.5f, { windowSize.x / 2.f, windowSize.y / 2.f + 80.f });

    auto back = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
    back->setText("back");
    back->setFontSize(72.f);
    back->setOrigin({ .5f, .5f });
    back->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 220.f });
    back->setBackgroundColor(sf::Color(129, 98, 113, 255));
    back->setOnClick([]() {
        Game::getInstance().changeState(std::make_shared<MenuState>());
        });
    UiManager::getInstance().addElement(back);
}

void SettingsState::update(float deltaTime)
{
    UiManager::getInstance().updateAll(deltaTime);
}

void SettingsState::draw(sf::RenderWindow* window)
{
}

void SettingsState::ui(sf::RenderWindow* window)
{
    UiManager::getInstance().drawAll(window);
}

void SettingsState::restart()
{
}
