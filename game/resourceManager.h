#pragma once

#include <SFML/Graphics.hpp>
#include "singleton.h"
#include <map>
#include <string>

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	enum class Texture {
		player = 0,
		enemy = 1,
		arms = 2,
		knife = 3,
		pistol = 4,
		rifle = 5,
		shotgun = 6,
		pistol_bullet = 14,
		rifle_bullet = 15,
		shotgun_bullet = 16,
		knife_item = 103,
		pistol_item = 104,
		rifle_item = 105,
		shotgun_item = 106,
		pistol_bullet_item = 204,
		rifle_bullet_item = 205,
		shotgun_bullet_item = 206,
        heal_item = 207,
		tile = 10
	};
	enum class Font {
		main = 0
	};

private:
	ResourceManager() = default;

	std::map<Texture, sf::Texture> textures;
	std::map<Font, sf::Font> fonts;

	void loadTexture(const Texture texture, const std::string& filepath);
	void loadFont(const Font font, const std::string& filepath);

public:

	void loadAssets();

	sf::Texture& getTexture(const Texture texture);
	sf::Font& getFont(const Font font);
};