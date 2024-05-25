#pragma once
#include "StaticGameObject.h"
class Grass :
	public StaticGameObject
{
public:
	Grass(sf::Vector2f pos);
	virtual void draw(sf::RenderWindow &);
	const sf::Sprite& get_pic() const;
	 sf::Vector2f get_position() const;


	Grass();
	~Grass();
private:
	static bool m_registerit;

};

