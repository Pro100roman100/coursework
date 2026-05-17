#pragma once

#include <SFML/Graphics.hpp>

constexpr int tileSize = 16;
constexpr sf::Vector2f windowSize(1600, 900);
constexpr float pixelRatio = windowSize.x / (20.f * 16.f);
constexpr sf::Vector2f sceneSize(windowSize / pixelRatio);

enum Direction
{
    Down = 0,
    Right = 1,
    Up = 2,
    Left = 3,
};
