#include "Boss.h"
#include "GameObject.h"


bool Boss::m_registerit = FactoryEnemy::registerit("Boss",
	[](const sf::Vector2f& pos, sf::RenderWindow & window) -> std::unique_ptr<Enemy> { return std::make_unique<Boss>(pos, window); });

Boss::Boss(sf::Vector2f pos, sf::RenderWindow & window)
	:Enemy(pos, window)
{
	// load the animation picture
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(BOSS_ANIMATION1))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(BOSS_ANIMATION2))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(BOSS_ANIMATION3))));
	m_pic.setTexture(*m_walking_animation[m_index_animation]);
	m_pic.setPosition(pos); // setting the position
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2); // center of pic
}

// draw picture
void Boss::draw(sf::RenderWindow & window)
{
	window.draw(m_pic);
}

sf::Vector2f Boss::get_position() const
{
	return m_position;
}

const sf::Sprite & Boss::get_pic() const
{
	return m_pic;
}

// in charge of preseneting the animation
void Boss::animate()
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

// in charge of preseneting the animation
void Boss::update(sf::Vector2f centerPos)
{
	int x_distance = abs(centerPos.x - m_pic.getPosition().x),
		y_distance = abs(centerPos.y - m_pic.getPosition().y);

	int x_movement = centerPos.x - m_pic.getPosition().x ,
		y_movement = centerPos.y - m_pic.getPosition().y;

	int x_pic_move,
		y_pic_move;

	if (x_movement>0)
		x_pic_move = 1.7f;
	else
		x_pic_move = -1.7f;

	if (y_movement>0)
		y_pic_move = 1.7f;
	else
		y_pic_move = -1.7f;
	
	if (x_distance < 350 && y_distance < 350)
	{
		if (x_distance > 15 && y_distance > 15)
			m_pic.move(x_pic_move, y_pic_move);
		else if (x_distance > 15)
			m_pic.move(x_pic_move, 0);
		else if (y_distance > 15)
			m_pic.move(0, y_pic_move);
	}


}


void Boss::flip_pic_left()
{
	m_pic.setScale(-1.f, 1.f);
}

void Boss::flip_pic_right()
{
	m_pic.setScale(1.f, 1.f);
}

void Boss::SetDelta(float time)
{

	m_delta = time;
}



Boss::~Boss()
{
}
