#include "resourceManager.h"
#include <stdexcept>
#include <iostream>

void ResourceManager::loadTexture(const Texture name, const std::string& filepath)
{
    if (textures.find(name) != textures.end())
        return;

    sf::Texture texture;
    if (!texture.loadFromFile(filepath))
        throw std::runtime_error("Failed to load texture: " + filepath);

    textures[name] = texture;
}

void ResourceManager::loadFont(const Font name, const std::string& filepath)
{
    if (fonts.find(name) != fonts.end())
        return;

    sf::Font font;
    if (!font.openFromFile(filepath))
        throw std::runtime_error("Failed to load font: " + filepath);

    fonts[name] = font;
}

void ResourceManager::loadAssets()
{
    try {
        loadFont(Font::main, "GFX/6px-Normal.ttf");
        loadTexture(Texture::player, "GFX/player.png");
        loadTexture(Texture::enemy, "GFX/enemy.png");
        loadTexture(Texture::arms, "GFX/arms.png");
        loadTexture(Texture::knife, "GFX/knife.png");
        loadTexture(Texture::pistol, "GFX/pistol.png");
        loadTexture(Texture::rifle, "GFX/rifle.png");
        loadTexture(Texture::shotgun, "GFX/rifle.png");
        loadTexture(Texture::pistol_bullet, "GFX/pistol_bullet.png");
        loadTexture(Texture::rifle_bullet, "GFX/rifle_bullet.png");
        loadTexture(Texture::shotgun_bullet, "GFX/shotgun_bullet.png");
        loadTexture(Texture::knife_item, "GFX/knife_item.png");
        loadTexture(Texture::pistol_item, "GFX/pistol_item.png");
        loadTexture(Texture::rifle_item, "GFX/rifle_item.png");
        loadTexture(Texture::shotgun_item, "GFX/shotgun_item.png");
        loadTexture(Texture::pistol_bullet_item, "GFX/pistol_bullet_item.png");
        loadTexture(Texture::rifle_bullet_item, "GFX/rifle_bullet_item.png");
        loadTexture(Texture::shotgun_bullet_item, "GFX/shotgun_bullet_item.png");
        loadTexture(Texture::heal_item, "GFX/heal_item.png");
        loadTexture(Texture::tile, "GFX/tile.png");
        loadTexture(Texture::knife_effect, "GFX/knife_effect.png");
    }
    catch (std::runtime_error err) {
        std::cerr << "Runtime error: " << err.what() << std::endl;
    }
}

sf::Texture& ResourceManager::getTexture(const Texture name)
{
    auto it = textures.find(name);
    if (it == textures.end())
        std::cerr << "Texture not found: " << static_cast<int>(name) << std::endl;
    return it->second;
}

sf::Font& ResourceManager::getFont(const Font name)
{
    auto it = fonts.find(name);
    if (it == fonts.end())
        std::cerr << "Font not found: " << static_cast<int>(name) << std::endl;
    return it->second;
}