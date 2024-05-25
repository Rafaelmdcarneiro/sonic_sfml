#pragma once
#include "GameObject.h"
#include"FactoryStatic.h"

class StaticGameObject :
	public GameObject
{
public:
	StaticGameObject(sf::Vector2f pos);
	StaticGameObject();
	const sf::Sprite& get_pic() const;

	virtual void draw(sf::RenderWindow &)=0;
	virtual sf::Vector2f get_position() const = 0;


	~StaticGameObject();
protected:

	sf::Sprite m_pic;

};

