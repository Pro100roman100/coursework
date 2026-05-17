#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"


int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow window(sf::VideoMode(static_cast<sf::Vector2u>(windowSize)), "Coursework", sf::Style::Close);
    window.setFramerateLimit(165.f);

    Game& game = Game::getInstance();
    game.init(&window);

    while (window.isOpen()) {
        //Event handling
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                game.mousePress(*mousePressed);
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    game.onEscapePressed();
                if (keyPressed->scancode == sf::Keyboard::Scancode::F1)
                    game.toggleFPS();
                if (keyPressed->scancode == sf::Keyboard::Scancode::F2)
                    game.toggleColliders();
                if (keyPressed->scancode == sf::Keyboard::Scancode::F3)
                    game.toggleCoordinates();
                if (keyPressed->scancode == sf::Keyboard::Scancode::R)
                    game.restart();
            }
        }

        //update
        game.update();
    }

    game.cleanup();
}