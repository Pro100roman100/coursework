#include "levelSelectState.h"

#include "game.h"
#include "menuState.h"
#include "playState.h"
#include "globalData.h"

#include <algorithm>

static bool isLevelCompleted(const std::string& mapName)
{
    return std::find(globalData::completedMaps.begin(), globalData::completedMaps.end(), mapName) != globalData::completedMaps.end();
}

LevelSelectState::LevelSelectState()
{
    uiManager->clear();

    auto title = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
    title->setText("Select level");
    title->setOrigin({ .5f, .5f });
    title->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f - 180.f });
    title->setFontSize(96.f);
    uiManager->addElement(title);

    const bool level1Unlocked = true;
    const bool level2Unlocked = isLevelCompleted("map");
    const bool level3Unlocked = isLevelCompleted("map1");
    const bool level4Unlocked = isLevelCompleted("map2");

    auto addLevelButton = [this](int levelNumber, const std::string& mapName, sf::Vector2f position, bool unlocked) {
        auto button = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
        button->setText("level " + std::to_string(levelNumber));
        button->setFontSize(72.f);
        button->setOrigin({ .5f, .5f });
        button->setPosition(position);
        button->setBackgroundColor(unlocked ? sf::Color(129, 98, 113, 255) : sf::Color(62, 47, 54, 255));
        button->setOnClick([mapName, unlocked]() {
            if (!unlocked)
                return;
            globalData::currentMap = mapName;
            Game::getInstance().changeState(std::make_shared<PlayState>());
        });
        uiManager->addElement(button);
    };

    addLevelButton(1, "map", { windowSize.x / 2.f, windowSize.y / 2.f - 80.f }, level1Unlocked);
    addLevelButton(2, "map1", { windowSize.x / 2.f, windowSize.y / 2.f }, level2Unlocked);
    addLevelButton(3, "map2", { windowSize.x / 2.f, windowSize.y / 2.f + 80.f }, level3Unlocked);
    addLevelButton(4, "map3", { windowSize.x / 2.f, windowSize.y / 2.f + 160.f }, level4Unlocked);

    auto back = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
    back->setText("back");
    back->setFontSize(72.f);
    back->setOrigin({ .5f, .5f });
  back->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 260.f });
    back->setBackgroundColor(sf::Color(129, 98, 113, 255));
    back->setOnClick([]() {
        Game::getInstance().changeState(std::make_shared<MenuState>());
    });
    uiManager->addElement(back);
}

void LevelSelectState::update(float deltaTime)
{
    uiManager->updateAll(deltaTime);
}

void LevelSelectState::draw(sf::RenderWindow* window)
{
}

void LevelSelectState::ui(sf::RenderWindow* window)
{
    uiManager->drawAll(window);
}

void LevelSelectState::restart()
{
}

void LevelSelectState::escape()
{
    Game::getInstance().changeState(std::make_shared<MenuState>());
}
