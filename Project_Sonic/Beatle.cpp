#include "Beatle.h"
#include "GameObject.h"


bool Beatle::m_registerit = FactoryEnemy::registerit("Beatle",
	[](const sf::Vector2f& pos, sf::RenderWindow & window) -> std::unique_ptr<Enemy> { return std::make_unique<Beatle>(pos, window); });

Beatle::Beatle(sf::Vector2f pos, sf::RenderWindow & window)
	:Enemy(pos, window)
{
	// load the animation texture
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(BAETLE_ANIMATION1))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(BAETLE_ANIMATION2))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(BAETLE_ANIMATION3))));
	m_pic.setTexture(*m_walking_animation[m_index_animation]);
	m_pic.setPosition(pos); // setting the position
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center of pic
}

// draw picture
void Beatle::draw(sf::RenderWindow & window)
{
	window.draw(m_pic);

}

sf::Vector2f Beatle::get_position() const
{
	return m_position;
}

const sf::Sprite & Beatle::get_pic() const
{
	return m_pic;
}

// in charge of preseneting the animation

void Beatle::animate()
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

// in charge of moving the crab

void Beatle::update(sf::Vector2f centerPos)
{

	float time = m_movement_clock.getElapsedTime().asSeconds();
	m_previous_pos = m_pic.getPosition();

	if (time < 2)
	{
		m_pic.move(300 * m_delta, 0);
		flip_pic_right();
	}
	
	else
	{
		m_pic.move(-300 * m_delta, 0);
		flip_pic_left();
		if (time > 4)
			m_movement_clock.restart();
	}
}


void Beatle::flip_pic_left()
{
	m_pic.setScale(1.f, 1.f);
}

void Beatle::flip_pic_right()
{
	
	m_pic.setScale(-1.f, 1.f);
}

// seeting m_delta
void Beatle::SetDelta(float time)
{

	m_delta = time;
}



Beatle::~Beatle()
{
}
