#include "DynamicGameObject.h"



DynamicGameObject::DynamicGameObject(sf::Vector2f pos, sf::RenderWindow &window)
	:GameObject(pos), m_window(window)
{
}

DynamicGameObject::~DynamicGameObject()
{
}
