#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>
#include <string>
#include "Constants.h"
#include <exception>


class ResourceManager
{
public:

	static ResourceManager & instance();

	const sf::Texture & GetTexture(const std::string &);
	const sf::SoundBuffer & GetAudio(const std::string &);

	const sf::Font & GetFont() const;

	~ResourceManager();

private:
	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	std::map <std::string, sf::Texture> m_pictures;
	std::map <std::string, sf::SoundBuffer> m_sounds;
	sf::Font m_font;
};

