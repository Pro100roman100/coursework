#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class UiElement : public sf::Drawable
{
private:
    std::function<void(float)> updateFunc = [](float) {};
    std::function<void()> onClickFunc = []() {};
protected:

    UiElement() = default;

public:
    virtual ~UiElement() = default;

    void setUpdate(std::function<void(float)> function);
    void setOnClick(std::function<void()> function);

    void update(float deltaTime);
    void onClick();

    virtual void setPosition(sf::Vector2f position) = 0;
    virtual void setScale(sf::Vector2f size) = 0;
    virtual void setOrigin(sf::Vector2f origin) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool isPointInside(const sf::Vector2f point) const = 0;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};