#include "StaticGameObject.h"




StaticGameObject::StaticGameObject(sf::Vector2f pos)
	:GameObject(pos)
{
}

StaticGameObject::StaticGameObject()
{
}

const sf::Sprite & StaticGameObject::get_pic() const
{
	return m_pic;
}

StaticGameObject::~StaticGameObject()
{
}
