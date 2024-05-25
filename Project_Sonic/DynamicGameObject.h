#pragma once
#include "GameObject.h"
#include "FactoryEnemy.h"

class DynamicGameObject:public GameObject
{
public:
	DynamicGameObject(sf::Vector2f pos, sf::RenderWindow &);

	void draw(sf::RenderWindow &) = 0;
	virtual sf::Vector2f get_position() const = 0;
	~DynamicGameObject();

protected:
	sf::RenderWindow &m_window;
};

