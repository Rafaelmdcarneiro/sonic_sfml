#include "Diamond.h"



Diamond::Diamond(sf::Vector2f pos)
	:Collectable(pos)
{
	m_pic.setTexture(ResourceManager::instance().GetTexture(DIAMOND)); // set picture
	m_pic.setPosition(pos); // set position
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center of pic
}

// draw pic
void Diamond::draw(sf::RenderWindow & window)
{
	window.draw(m_pic);
}

// get position
sf::Vector2f Diamond::get_position() const
{
	return m_position;
}


Diamond::~Diamond()
{
}
