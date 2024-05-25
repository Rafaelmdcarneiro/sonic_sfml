#pragma once
#include "Character.h"
class Enemy :
	public Character
{
public:
	Enemy(sf::Vector2f pos, sf::RenderWindow & window);
	void draw(sf::RenderWindow &) = 0;
	virtual void animate() = 0;
	virtual void update(sf::Vector2f centerPos) = 0;
	virtual void SetDelta(float) =0;
	virtual int GetLife() const ;
	virtual void SetLife(int);
	sf::Vector2f GetPreviousPos() const;
	void SetPreviousPos(sf::Vector2f);
	void SetPosition(sf::Vector2f pos);
	void explosion();

	~Enemy();
};

