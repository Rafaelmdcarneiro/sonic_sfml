#include "FactoryEnemy.h"
#include "Enemy.h"


// according to design pattren


std::unique_ptr<Enemy> FactoryEnemy::create(const std::string & name, const sf::Vector2f & pos, sf::RenderWindow & window)
{
	auto it = getMap().find(name);
	if (it == getMap().end())
		throw std::runtime_error("object to create not found");
	return it->second(pos, window);
}

bool FactoryEnemy::registerit(const std::string & name, std::unique_ptr<Enemy>(*f)(const sf::Vector2f &pos, sf::RenderWindow &window))
{
	getMap().emplace(name, f);
	
	return true;
}
