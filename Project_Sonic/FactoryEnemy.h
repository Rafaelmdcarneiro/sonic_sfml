#pragma once
#include <memory>
#include <string>
#include <map>
#include <SFML\Graphics.hpp>
#include <exception>

class Enemy;

typedef std::map<std::string, std::unique_ptr<Enemy>(*)(const sf::Vector2f & pos, sf::RenderWindow & window)> mymap;

class FactoryEnemy
{
public:
	
	static std::unique_ptr < Enemy > create(const std::string& name, const sf::Vector2f & pos, sf::RenderWindow & window);
	static bool registerit(const std::string& name, std::unique_ptr<Enemy>(*f)(const sf::Vector2f& pos, sf::RenderWindow & window));

private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};


