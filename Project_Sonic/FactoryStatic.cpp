#include "FactoryStatic.h"
#include "StaticGameObject.h"

// according to design pattren


std::unique_ptr<StaticGameObject> FactoryStatic::create(const std::string& name, const sf::Vector2f & pos)
{
	
	auto it = FactoryStatic::get_FactoryStatic().find(name);

	if (it == FactoryStatic::get_FactoryStatic().end())
		throw std::runtime_error("object to create not found");
	return it->second(pos); 
}


bool FactoryStatic::registerit(const std::string& name, std::unique_ptr<StaticGameObject>(*f)(const sf::Vector2f& pos))
{
	
	FactoryStatic::get_FactoryStatic().emplace(name, f);
	return true;
}

 std::map<std::string, std::unique_ptr<StaticGameObject>(*)(const sf::Vector2f&pos)> &FactoryStatic::get_FactoryStatic()
{
	static  FactoryStatic m_factory_static;
	return m_factory_static.m_map;
}

