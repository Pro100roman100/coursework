#include "playState.h"

#include "player.h"
#include "camera.h"
#include "game.h"
#include "endGameState.h"

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
	UiManager::getInstance().addElement(weaponImage);

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
	UiManager::getInstance().addElement(ammoText);

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
	UiManager::getInstance().addElement(healthText);

	auto startText = std::make_shared<Text>(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	startText->setText("Kill all enemies");
	startText->setOrigin({ .5f, .5f });
	startText->setPosition(windowSize / 2.f);
	startText->setFontSize(64.f);
	float timer = 2.f;
	startText->setUpdate([timer, startText](float deltaTime) mutable {
		timer -= deltaTime;
		if (timer <= 0)
			UiManager::getInstance().removeElement(startText.get());
		});
	UiManager::getInstance().addElement(startText);
}

PlayState::PlayState()
{
	ObjectManager::getInstance().clear();
	PhysicsManager::getInstance().clear();
	UiManager::getInstance().clear();

	if (!FileManager::loadFromFile(globalData::currentMap + ".txt"))
		std::cout << "Failed to load " << globalData::currentMap << std::endl;

	initUI();
}

void PlayState::update(float deltaTime)
{
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

	UiManager::getInstance().updateAll(deltaTime);
}

void PlayState::draw(sf::RenderWindow* window)
{
	ObjectManager::getInstance().drawAll(window);
}

void PlayState::ui(sf::RenderWindow* window)
{
	UiManager::getInstance().drawAll(window);
}

void PlayState::restart()
{
	Game::getInstance().changeState(std::make_shared<PlayState>());
}