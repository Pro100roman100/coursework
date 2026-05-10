#pragma once

#include <SFML/Graphics.hpp>

constexpr int tileSize = 16;
constexpr sf::Vector2f sceneSize(tileSize * 14, tileSize * 9);
constexpr float pixelRatio = 6 / 1;
constexpr sf::Vector2f windowSize(sceneSize * pixelRatio);

enum Direction
{
    Down = 0,
    Right = 1,
    Up = 2,
    Left = 3,
};
