#include "text.h"

Text::Text(const sf::Font& font) : text(font)
{
}

void Text::setText(const std::string& string)
{
    text.setString(string);
    setOrigin(origin);
}

void Text::setFontSize(float size)
{
    text.setCharacterSize(size);
    setOrigin(origin);
}

void Text::setPosition(sf::Vector2f position)
{
    position.y -= text.getCharacterSize() / 2;
    text.setPosition(position);
}

void Text::setScale(sf::Vector2f size)
{
    text.setScale(size);
}

void Text::setOrigin(sf::Vector2f origin)
{
    this->origin = origin;
    text.setOrigin(sf::Vector2f(origin.x * text.getLocalBounds().size.x, origin.y * text.getLocalBounds().size.y));
}

sf::FloatRect Text::getBounds() const
{
    return text.getGlobalBounds();
}

bool Text::isPointInside(const sf::Vector2f point) const
{
    return text.getGlobalBounds().contains(point);
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
