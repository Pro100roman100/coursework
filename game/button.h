#pragma once

#include "uiElement.h"

class Button : public UiElement {
private:
	sf::RectangleShape background;
	sf::Text text;
	sf::Vector2f origin{ 0.f,0.f };

public:
	Button(sf::Font& font);

	void setText(const std::string& string);
	void setFontSize(float size);
	void setSize(sf::Vector2f size);
	void setBackgroundColor(sf::Color color);

	void setPosition(sf::Vector2f position) override;
	void setScale(sf::Vector2f size) override;
	void setOrigin(sf::Vector2f origin) override;
	sf::FloatRect getBounds() const override;
	bool isPointInside(const sf::Vector2f point) const override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
