#include "playState.h"

#include "player.h"
#include "camera.h"
#include "game.h"
#include "endGameState.h"
#include "button.h"
#include "menuState.h"

void PlayState::initUI()
{
	auto weaponImage = std::make_shared<Image>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::knife_item));
	weaponImage->setScale(sf::Vector2f(1, 1) * pixelRatio);
	weaponImage->setPosition(sf::Vector2f(10.f, windowSize.y - 10.f));
	weaponImage->setOrigin(sf::Vector2f(0, 1));
	weaponImage->setUpdate([weaponImage](float) {
		auto player = Player::getActive();
		if (player == nullptr)
			return;
		switch (player->getInventory().getCurrentWeapon()->getType())
		{
		case WeaponType::Knife:
			weaponImage->setImage(ResourceManager::getInstance().getTexture(ResourceManager::Texture::knife_item));
			break;
		case WeaponType::Pistol:
			weaponImage->setImage(ResourceManager::getInstance().getTexture(ResourceManager::Texture::pistol_item));
			break;
		case WeaponType::Rifle:
			weaponImage->setImage(ResourceManager::getInstance().getTexture(ResourceManager::Texture::rifle_item));
			break;
		case WeaponType::Shotgun:
			weaponImage->setImage(ResourceManager::getInstance().getTexture(ResourceManager::Texture::shotgun_item));
			break;
		default:
			break;
		}
		});
	uiManager->addElement(weaponImage);

	auto ammoText = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	ammoText->setText("0");
	ammoText->setOrigin({ 0.f, 1.f });
	ammoText->setPosition(sf::Vector2f(110.f, windowSize.y - 15.f));
	ammoText->setFontSize(48.f);
	ammoText->setUpdate([ammoText](float) {
		auto player = Player::getActive();
		if (player == nullptr)
			return;
		auto weaponType = player->getInventory().getCurrentWeapon()->getType();
		int ammo = player->getInventory().getAmmo(weaponType);

		if(weaponType != WeaponType::Knife)
			ammoText->setText(std::to_string(ammo));
		else
			ammoText->setText("");
		});
	uiManager->addElement(ammoText);

	auto healthText = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	healthText->setText("100");
	healthText->setOrigin({ 1.f, 1.f });
	healthText->setPosition(sf::Vector2f(windowSize.x - 10.f, windowSize.y - 15.f));
	healthText->setFontSize(48.f);
	healthText->setUpdate([healthText](float) {
		auto player = Player::getActive();
		if (player == nullptr)
			return;
		healthText->setText(std::to_string(player->getHealth()));
		});
	uiManager->addElement(healthText);

	auto startText = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	startText->setText("Kill all enemies");
	startText->setOrigin({ .5f, .5f });
	startText->setPosition(windowSize / 2.f);
	startText->setFontSize(64.f);
	float timer = 2.f;
	startText->setUpdate([timer, this, startText](float deltaTime) mutable {
		timer -= deltaTime;
		if (timer <= 0)
			uiManager->removeElement(startText.get());
		});
	uiManager->addElement(startText);

	auto menuButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	menuButton->setText("menu");
	menuButton->setFontSize(42.f);
	menuButton->setOrigin({ 0.f, 0.f });
	menuButton->setPosition({ 10.f, 40.f });
	menuButton->setSize({ 100.f, 36.f });
	menuButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	menuButton->setOnClick([]() {
		Game::getInstance().changeState(std::make_shared<MenuState>());
		});
	uiManager->addElement(menuButton);

	initPauseMenu();
}

PlayState::PlayState()
{
	ObjectManager::getInstance().clear();
	PhysicsManager::getInstance().clear();
	uiManager->clear();

	pauseUiManager = std::make_shared<UiManager>();

	if (!FileManager::loadFromFile(globalData::currentMap))
		std::cout << "Failed to load " << globalData::currentMap << std::endl;

	initUI();
}

void PlayState::update(float deltaTime)
{
	if (isPaused) {
		pauseUiManager->updateAll(deltaTime);
		return;
	}

	ObjectManager::getInstance().updateAll(deltaTime);
	PhysicsManager::getInstance().update(deltaTime);

	if (Player::getActive() == nullptr) {
		globalData::endState = globalData::lose;
		Game::getInstance().changeState(std::make_shared<EndGameState>());
		return;
	}
	if (Game::getInstance().getEnemyCount() <= 0) {
		globalData::endState = globalData::win;
		Game::getInstance().changeState(std::make_shared<EndGameState>());
		return;
	}

	uiManager->updateAll(deltaTime);
}

void PlayState::draw(sf::RenderWindow* window)
{
	ObjectManager::getInstance().drawAll(window);
}

void PlayState::ui(sf::RenderWindow* window)
{

	if (isPaused) {
		auto pauseOverlay = std::make_shared<sf::RectangleShape>(windowSize);
		pauseOverlay->setFillColor(sf::Color(0, 0, 0, 150));
		window->draw(*pauseOverlay);

		pauseUiManager->drawAll(window);
	}
	else
		uiManager->drawAll(window);
}

void PlayState::restart()
{
	Game::getInstance().changeState(std::make_shared<PlayState>());
}

void PlayState::handleClick(const sf::Vector2f& clickPos)
{
	if (isPaused) {
		pauseUiManager->handleClick(clickPos);
	} else {
		uiManager->handleClick(clickPos);
	}
}

void PlayState::escape()
{
	isPaused = !isPaused;
}

void PlayState::initPauseMenu()
{
	auto pauseText = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	pauseText->setText("PAUSED");
	pauseText->setOrigin({ .5f, .5f });
	pauseText->setPosition(windowSize / 2.f - sf::Vector2f(0.f, 80.f));
	pauseText->setFontSize(128.f);
	pauseUiManager->addElement(pauseText);

	auto instructionsText = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	instructionsText->setText("Controls:\nWASD or arrow keys > Move\nmouse > Aim\nclick or space > Attack\nnumber keys > Switch weapon");
	instructionsText->setOrigin({ 0, 0 });
	instructionsText->setPosition({ 10.f, 10.f });
	instructionsText->setFontSize(36.f);
	pauseUiManager->addElement(instructionsText);

	auto resumeButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	resumeButton->setText("main menu");
	resumeButton->setFontSize(72.f);
	resumeButton->setOrigin({ .5f, .5f });
	resumeButton->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 90.f });
	resumeButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	resumeButton->setOnClick([this]() {
		Game::getInstance().changeState(std::make_shared<MenuState>());
	});
	pauseUiManager->addElement(resumeButton);

	auto mainMenuButton = std::make_shared<Button>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	mainMenuButton->setText("exit");
	mainMenuButton->setFontSize(72.f);
	mainMenuButton->setOrigin({ .5f, .5f });
	mainMenuButton->setPosition({ windowSize.x / 2.f, windowSize.y / 2.f + 170.f });
	mainMenuButton->setBackgroundColor(sf::Color(129, 98, 113, 255));
	mainMenuButton->setOnClick([]() {
		Game::getInstance().closeGame();
	});
	pauseUiManager->addElement(mainMenuButton);
}