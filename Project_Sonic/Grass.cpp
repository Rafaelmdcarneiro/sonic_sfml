#include "Grass.h"




bool Grass::m_registerit = FactoryStatic::registerit("Grass",
	[](const sf::Vector2f& pos) -> std::unique_ptr<StaticGameObject> { return std::make_unique<Grass>(pos); });


Grass::Grass(sf::Vector2f pos)
	:StaticGameObject(pos)
{
	m_pic.setTexture(ResourceManager::instance().GetTexture(GRASS)); // set picture
	m_pic.setPosition(m_position); // set position
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center pic
}

Grass::Grass()
{
}

// draw picture

void Grass::draw(sf::RenderWindow & window)
{
	window.draw(m_pic);
}

// get m_mpic
const sf::Sprite & Grass::get_pic() const
{
	return StaticGameObject::m_pic;
}

// get position
sf::Vector2f Grass::get_position() const
{
	return m_position;
}


Grass::~Grass()
{
}

