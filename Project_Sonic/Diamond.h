#pragma once
#include "Collectable.h"
class Diamond :
	public Collectable
{
public:
	Diamond(sf::Vector2f pos);
	void draw(sf::RenderWindow&);
	sf::Vector2f get_position() const;


	~Diamond();

private:
	

};

