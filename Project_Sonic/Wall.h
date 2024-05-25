#pragma once
#include "StaticGameObject.h"



class Wall :
	public StaticGameObject
{
public:
	Wall(sf::Vector2f pos);
	void draw(sf::RenderWindow &);
	const sf::Sprite& get_pic() const;
	sf::Vector2f get_position() const;
	Wall();
	~Wall();
private:
	static bool m_registerit;
};

