#pragma once
#include "Collectable.h"
class Ring :
	public Collectable
{
public:
	Ring(sf::Vector2f pos);
	 void draw(sf::RenderWindow&);
	 sf::Vector2f get_position() const;
	~Ring();

private:
	

};

