#include "Crab.h"



bool Crab::m_registerit = FactoryEnemy::registerit("Crab",
	[](const sf::Vector2f& pos, sf::RenderWindow & window) -> std::unique_ptr<Enemy> { return std::make_unique<Crab>(pos, window); });


Crab::Crab(sf::Vector2f pos, sf::RenderWindow & window)
	:Enemy(pos, window)
{
	// load the animation picture
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(CRAB_ANIMATION1))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(CRAB_ANIMATION2))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(CRAB_ANIMATION3))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(CRAB_ANIMATION4))));

	m_pic.setTexture(*m_walking_animation[m_index_animation]);
	m_pic.setTexture(*m_walking_animation[m_index_animation]);
	m_pic.setPosition(pos); // set position
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center of the pic

}

// draw the pic
void Crab::draw(sf::RenderWindow & window)
{
	window.draw(m_pic);
}

sf::Vector2f Crab::get_position() const
{
	return m_position;
}

const sf::Sprite & Crab::get_pic() const
{
	return m_pic;
}
// in charge of moving the crab
void Crab::update(sf::Vector2f centerPos)
{

	float time = m_movement_clock.getElapsedTime().asSeconds();
	m_previous_pos = m_pic.getPosition();

	if (time < 2)
		m_pic.move(300 * m_delta, 0);

	else
	{
		m_pic.move(-300 * m_delta, 0);
		
		if (time > 4)
			m_movement_clock.restart();
	}

}


// flip the picture to left
void Crab::flip_pic_left()
{
	m_pic.setScale(-1.f, 1.f);
}
// flip the picture to right

void Crab::flip_pic_right()
{
	m_pic.setScale(1.f, 1.f);
}
// setting m_delta
void Crab::SetDelta(float time)
{
	m_delta = time;
}

// in charge of preseneting the animation
void Crab::animate()
{
	if (m_clock.getElapsedTime().asSeconds() > 0.1)
	{
		if (m_index_animation < m_walking_animation.size() - 1)
			m_index_animation++;
		else
			m_index_animation = 0;

		m_pic.setTexture(*m_walking_animation[m_index_animation]);
		
		m_clock.restart();
	}

}


Crab::~Crab()
{
}
