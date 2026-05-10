#include "button.h"

Button::Button(sf::Font& font) : text(font)
{

}

void Button::setText(const std::string& string)
{
	text.setString(string);
	setSize(text.getLocalBounds().size * 1.4f);
	setOrigin(origin);
}

void Button::setFontSize(float size)
{
	text.setCharacterSize(size);
	setSize(text.getLocalBounds().size * 1.4f);
	setOrigin(origin);
}

void Button::setSize(sf::Vector2f size)
{
	background.setSize(size);
}

void Button::setBackgroundColor(sf::Color color)
{
	background.setFillColor(color);
}

void Button::setPosition(sf::Vector2f position)
{
	background.setPosition(position);
	position.y -= (text.getCharacterSize() * 4 / 5) / 2;
	text.setPosition(position);
}

void Button::setScale(sf::Vector2f size)
{
	text.setScale(size);
	background.setScale(size);
}

void Button::setOrigin(sf::Vector2f origin)
{
	this->origin = origin;
	text.setOrigin(sf::Vector2f(origin.x * text.getLocalBounds().size.x, origin.y * text.getLocalBounds().size.y));
	background.setOrigin(sf::Vector2f(origin.x * background.getLocalBounds().size.x, origin.y * background.getLocalBounds().size.y));
}

sf::FloatRect Button::getBounds() const
{
	return background.getGlobalBounds();
}

bool Button::isPointInside(const sf::Vector2f point) const
{
	return background.getGlobalBounds().contains(point);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);
}
