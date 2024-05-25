#include "Ring.h"




Ring::Ring(sf::Vector2f pos)
	:Collectable(pos)
{
	m_pic.setTexture(ResourceManager::instance().GetTexture(RING)); // set picture
	m_pic.setPosition(pos); // set pos
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center of pic


}
// draw picture

void Ring::draw(sf::RenderWindow & window)
{
	
	window.draw(m_pic);

}

// get position

sf::Vector2f Ring::get_position() const
{
	return m_position;
}


Ring::~Ring()
{
}
