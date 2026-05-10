#include "image.h"

Image::Image(const sf::Texture& texture) : sprite(texture)
{
}

void Image::setImage(const sf::Texture& texture)
{
    sprite.setTexture(texture);
}

void Image::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
}

void Image::setScale(sf::Vector2f scale)
{
    sprite.setScale(scale);
}

void Image::setOrigin(sf::Vector2f origin)
{
    sprite.setOrigin(sf::Vector2f(origin.x * sprite.getLocalBounds().size.x, origin.y * sprite.getLocalBounds().size.y));
}

sf::FloatRect Image::getBounds() const
{
    return sprite.getGlobalBounds();
}

bool Image::isPointInside(const sf::Vector2f point) const
{
    return sprite.getGlobalBounds().contains(point);
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
