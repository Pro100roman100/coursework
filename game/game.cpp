#include "game.h"
#include "inputManager.h"
#include <cstdlib>
#include <ctime>

void Game::init(sf::RenderWindow* window)
{
	srand(static_cast<unsigned>(time(0)));
	FileManager::loadData();

	this->window = window;

	ResourceManager::getInstance().loadAssets();

	defaultCamera.setActive();
	uiCamera.setSize(windowSize);
	uiCamera.setCenter(windowSize / 2.f);

	InputManager::getInstance().setWindow(window);

	changeState(std::make_shared<MenuState>());
}

void Game::restart()
{
	if (currentState != nullptr)
		currentState->restart();
}

void Game::toggleFPS()
{
	FPSToggle = !FPSToggle;
}

void Game::toggleColliders()
{
	collidersToggle = !collidersToggle;
}

void Game::toggleCoordinates()
{
	coordinatesToggle = !coordinatesToggle;
}

void Game::onEscapePressed()
{
	if (currentState == nullptr)
		return;

	currentState->escape();
}

void Game::mousePress(const sf::Event::MouseButtonPressed& mousePressed)
{
	if (mousePressed.button != sf::Mouse::Button::Left)
		return;

	if (currentState == nullptr)
		return;

	const sf::Vector2i pixelPos(mousePressed.position);
	const sf::Vector2f uiPos = window->mapPixelToCoords(pixelPos, uiCamera);
	currentState->handleClick(uiPos);
}

void Game::update()
{
	static sf::Clock clock;
	deltaTime = clock.restart().asSeconds();
	if (deltaTime > 1.f / 20.f)
		deltaTime = 1.f / 20.f;

	if (currentState == nullptr)
		std::cerr << "Game has no current state";

	currentState->update(deltaTime);
	if (Camera::getActive()) 
		Camera::getActive()->update(deltaTime);

	window->clear(sf::Color(153, 117, 119, 225));
	if (Camera::getActive())
		window->setView(Camera::getActive()->getView());
	currentState->draw(window);

	if (collidersToggle)
		PhysicsManager::getInstance().drawColliders(window);

	window->setView(uiCamera);
	currentState->ui(window);
	displayFPS();
	displayCoordinates();

	window->display();
}

void Game::changeState(std::shared_ptr<GameState> newState)
{
	currentState = newState;
}

void Game::displayFPS()
{
	static int frameCount = 0;
	static float fpsTimer = 0.f;

	fpsTimer += deltaTime;
	frameCount++;

	static sf::Text fpsText(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	fpsText.setCharacterSize(24);
	fpsText.setPosition(sf::Vector2f(10.0f, 10.0f));

	if (fpsTimer >= 0.5f) {
		fpsText.setString("FPS: " + std::to_string(static_cast<int>(frameCount / fpsTimer)));
		fpsTimer = 0.0f;
		frameCount = 0;
	}

	if (FPSToggle)
		window->draw(fpsText);
}

void Game::displayCoordinates()
{
	if (!coordinatesToggle)
		return;

	static sf::Text coordText(ResourceManager::getInstance().getFont(ResourceManager::Font::main));
	coordText.setCharacterSize(24);
	coordText.setFillColor(sf::Color::White);

	sf::View activeView = Camera::getActive()->getView();
	sf::Vector2f viewCenter = activeView.getCenter();
	sf::Vector2f viewSize = activeView.getSize();
	float viewLeft = viewCenter.x - viewSize.x / 2.f;
	float viewRight = viewCenter.x + viewSize.x / 2.f;
	float viewTop = viewCenter.y - viewSize.y / 2.f;
	float viewBottom = viewCenter.y + viewSize.y / 2.f;

	const auto& objects = ObjectManager::getInstance().getObjects();
	for (const auto& obj : objects) {
		if (!obj)
			continue;

		sf::Vector2f pos = obj->getPosition();

		if (pos.x < viewLeft || pos.x > viewRight || pos.y < viewTop || pos.y > viewBottom)
			continue;

		int tileX = static_cast<int>(pos.x / tileSize + .5f);
		int tileY = static_cast<int>(pos.y / tileSize + .5f);

		coordText.setPosition(static_cast<sf::Vector2f>(window->mapCoordsToPixel(pos, Camera::getActive()->getView())));
		coordText.setString(std::to_string(tileX) + "," + std::to_string(tileY));

		window->draw(coordText);
	}
}

void Game::cleanup() {
	currentState = nullptr;
	ObjectManager::getInstance().clear();
	PhysicsManager::getInstance().clear();
}

void Game::closeGame() {
	if (window != nullptr)
		window->close();
}

void Game::incrementEnemyCount()
{
	enemyCount++;
}

void Game::decrementEnemyCount()
{
	if (enemyCount > 0)
		enemyCount--;
}

int Game::getEnemyCount()
{
	return enemyCount;
}
