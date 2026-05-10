#pragma once

#include "uiElement.h"
#include <SFML/Graphics.hpp>
#include <string>

class Text : public UiElement {
private:
    sf::Text text;
    sf::Vector2f origin{0, 0};

public:
    Text(const sf::Font& font);

    void setText(const std::string& string);
    void setFontSize(float size);

    void setPosition(sf::Vector2f position) override;
    void setScale(sf::Vector2f size) override;
    void setOrigin(sf::Vector2f origin) override;
    sf::FloatRect getBounds() const override;
    bool isPointInside(const sf::Vector2f point) const override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
