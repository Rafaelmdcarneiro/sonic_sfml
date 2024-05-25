#pragma once
#include <memory>
#include <string>
#include <map>
#include <SFML\Graphics.hpp>
#include <exception>

class StaticGameObject;

class FactoryStatic
{
public:
	static std::unique_ptr < StaticGameObject > create(const std::string& name, const sf::Vector2f & pos);
	static bool registerit(const std::string& name, std::unique_ptr<StaticGameObject>(*f)(const sf::Vector2f& pos));
	static std::map<std::string, std::unique_ptr<StaticGameObject>(*)(const sf::Vector2f & pos)>& get_FactoryStatic();


private:
	std::map<std::string, std::unique_ptr<StaticGameObject>(*)(const sf::Vector2f & pos)> m_map;

};

