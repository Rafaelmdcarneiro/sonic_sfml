#include "Wall.h"
#include "Sonic.h"


bool Wall::m_registerit = FactoryStatic::registerit("Wall",
	[](const sf::Vector2f& pos) -> std::unique_ptr<StaticGameObject> { return std::make_unique<Wall>(pos); });

Wall::Wall(sf::Vector2f pos)
	:StaticGameObject(pos)
{
	m_pic.setTexture(ResourceManager::instance().GetTexture(WALL));  // setting picture
	m_pic.setPosition(pos); // setting position
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center of pic
}

Wall::Wall()
{
}

// draw the picture

void Wall::draw(sf::RenderWindow & window)
{
	window.draw(m_pic);
}

// gets the picture

const sf::Sprite & Wall::get_pic() const
{
	return StaticGameObject::m_pic;
}

// gets the position
sf::Vector2f Wall::get_position() const
{
	return m_position;
}


Wall::~Wall()
{
}

