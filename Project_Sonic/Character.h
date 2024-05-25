#pragma once
#include "DynamicGameObject.h"
class Character :
	public DynamicGameObject
{
public:
	Character(sf::Vector2f pos, sf::RenderWindow & window);
	void draw(sf::RenderWindow &) = 0;
	virtual const sf::Sprite &get_pic() const = 0;
	
	virtual sf::Vector2f get_position() const = 0;
	virtual int GetLife() const = 0;
	virtual void SetLife(int) = 0;

	~Character();

protected:
	std::vector< std::unique_ptr<sf::Texture> > m_walking_animation; // for the characters animation
	sf::Sprite m_pic;
	sf::Clock m_clock; // clock for the animation
	sf::Vector2f m_previous_pos;
	int m_life;
	int m_index_animation; // index of picture which presented in the vector of animation
};

