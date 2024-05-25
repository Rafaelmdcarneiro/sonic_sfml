#include "Enemy.h"



Enemy::Enemy(sf::Vector2f pos, sf::RenderWindow & window)
	:Character(pos, window)
{
	m_life = 1; // set life to 1
}


int Enemy::GetLife() const
{
	return m_life;
}

void Enemy::SetLife(int life)
{
	m_life = life;
}

// set m_pic to explosion picture
void Enemy::explosion()
{
	m_pic.setTexture(ResourceManager::instance().GetTexture(EXPLOSION)); 

}


sf::Vector2f Enemy::GetPreviousPos() const
{
	return m_previous_pos;
}	

void Enemy::SetPreviousPos(sf::Vector2f pos)
{
	m_previous_pos = pos;
}

void Enemy::SetPosition(sf::Vector2f pos)
{

	m_pic.setPosition(pos);
	m_position = pos;
}


Enemy::~Enemy()
{
}
