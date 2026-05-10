#include "uiManager.h"
#include <algorithm>

void UiManager::addElement(std::shared_ptr<UiElement> element)
{
    if (element)
        elements.push_back(element);
}

void UiManager::removeElement(UiElement* element)
{
    if (element) {
        auto it = std::find_if(elements.begin(), elements.end(),
            [element](const std::shared_ptr<UiElement>& e) { return e.get() == element; });

        if (it != elements.end())
            elements.erase(it);
    }
}

void UiManager::updateAll(float deltaTime)
{
    auto elementsCopy = elements;
    for (auto& element : elementsCopy) {
        element->update(deltaTime);
    }
}

void UiManager::drawAll(sf::RenderWindow* window)
{
    for (auto& element : elements) {
        window->draw(*element);
    }
}

void UiManager::handleClick(const sf::Vector2f& clickPos)
{
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        auto& element = *it;
        if (element && element->isPointInside(clickPos)) {
            element->onClick();
            return;
        }
    }
}

void UiManager::clear()
{
    elements.clear();
}
