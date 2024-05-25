#pragma once
#include "StaticGameObject.h"
class Collectable :
	public StaticGameObject
{
public:
	Collectable(sf::Vector2f pos);
	Collectable();
	virtual void draw(sf::RenderWindow&) = 0;
	virtual sf::Vector2f get_position() const = 0;


	~Collectable();

protected:
};	

