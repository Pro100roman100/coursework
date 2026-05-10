#pragma once

#include "uiElement.h"
#include <SFML/Graphics.hpp>

class Image : public UiElement {
protected:
    sf::Sprite sprite;

public:
    Image(const sf::Texture& texture);

    void setImage(const sf::Texture& texture);

    void setPosition(sf::Vector2f position) override;
    void setScale(sf::Vector2f size) override;
    void setOrigin(sf::Vector2f origin) override;

    sf::FloatRect getBounds() const override;

    bool isPointInside(const sf::Vector2f point) const override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
