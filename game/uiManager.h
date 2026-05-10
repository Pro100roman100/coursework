#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "uiElement.h"
#include "singleton.h"

class UiManager : public Singleton<UiManager>
{
    friend class Singleton<UiManager>;

private:
    UiManager() = default;

    std::vector<std::shared_ptr<UiElement>> elements;

public:
    void addElement(std::shared_ptr<UiElement> element);
    void removeElement(UiElement* element);

    const std::vector<std::shared_ptr<UiElement>>& getElements() const
    {
        return elements;
    }

    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow* window);

    void handleClick(const sf::Vector2f& clickPos);

    void clear();
};
