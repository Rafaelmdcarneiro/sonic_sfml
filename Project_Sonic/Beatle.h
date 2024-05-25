#pragma once
#include "Enemy.h"
class Beatle :
	public Enemy
{
public:
	Beatle(sf::Vector2f pos, sf::RenderWindow & window);
	void draw(sf::RenderWindow &);
	sf::Vector2f get_position() const;
	const sf::Sprite &get_pic() const;
	void update(sf::Vector2f centerPos);
	void flip_pic_left();
	void flip_pic_right();
	void SetDelta(float);

	void animate();

	~Beatle();

private:
	sf::Clock m_movement_clock; 
	float m_delta; // delta for the movement
	static bool m_registerit; // for the enemyfactor
};

