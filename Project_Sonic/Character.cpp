#include "Character.h"



Character::Character(sf::Vector2f pos, sf::RenderWindow & window)
	:DynamicGameObject(pos, window), m_index_animation(0)
{
}


Character::~Character()
{
}
