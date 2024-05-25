#include "Sonic.h"
#include "Wall.h"



Sonic::Sonic(sf::Vector2f pos, sf::RenderWindow & window)
	:Character(pos,window), faceright(true), m_state(std::make_unique<StandingState>()), m_window(window),
	m_index_jump_animation(0),m_while_jump(false), m_jump_height(220), m_gravity_acceleration(9.7),m_mass(45),m_fall_speed_value(0),
	m_acceleration_value(0),m_speed_value(0), m_eaten_diamonds(0), m_hit(false), m_player_score(0)
{
	// loading the animation pictures

	m_walking_animation.emplace_back(std::make_unique<sf::Texture> (std::move(ResourceManager::instance().GetTexture(SONIC_ANIMATION1))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(SONIC_ANIMATION2))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(SONIC_ANIMATION3))));
	m_walking_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(SONIC_ANIMATION4))));
	m_jumping_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(SONIC_JUMP1))));
	m_jumping_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(SONIC_JUMP2))));
	m_jumping_animation.emplace_back(std::make_unique<sf::Texture>(std::move(ResourceManager::instance().GetTexture(SONIC_JUMP3))));
	m_life = 5; // setting left
	m_pic.setTexture(*m_walking_animation[m_index_animation]); // setting picture
	m_pic.setPosition(pos); // setting the positon
	m_pic.setOrigin(m_pic.getGlobalBounds().width / 2, m_pic.getGlobalBounds().height / 2);   // center of the pic
}

// flip the picture to the left
void Sonic::flip_pic_left()
{
	m_pic.setScale(-1.f, 1.f);
}

// flip the picture to the right
void Sonic::flip_pic_right()
{
	m_pic.setScale(1.f, 1.f);
}

// set to standing picture
void Sonic::load_stand_image()
{
	m_pic.setTexture(*m_walking_animation[0]);
}

// this function in charge of moeving the player while he jumping
void Sonic::move_in_jump()
{
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		
		m_pic.move(350 * m_delta_time, 0);
		flip_pic_right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_pic.move(-350 * m_delta_time, 0);
		flip_pic_left();
	}

}

// set the while_jump
void Sonic::SetWhileJump(const bool var)
{
	m_while_jump = var;
}

// getting while jump
bool Sonic::GetWhileJump() const
{
	return m_while_jump;
}

// setting delta time in order to move sonic
void Sonic::set_delta_time(float new_time) // new
{
	m_delta_time = new_time;
}

// getting the player life
int Sonic::GetLife() const
{
	return Character::m_life;
}

// setting the player life
void Sonic::SetLife(int life)
{
	Character::m_life = life;
}

// getting the number of diamond which the player ate
int Sonic::GetEatenDiamonds() const
{
	return m_eaten_diamonds;
}

// setting the number of diamond which the player ate
void Sonic::SetEatenDiamonds(int value)
{
	m_eaten_diamonds = value;
}

// get the player score
int Sonic::GetScore() const
{
	return m_player_score;
}

// set the player score
void Sonic::SetScore(int score)
{
	m_player_score = score;
}

// get m_hit in order to know when to make sonic flash
bool Sonic::GetHit() const
{
	return m_hit;
}

// this function make sonic flashing
void Sonic::strike()
{
	static sf::Clock delay;  // clock for making sonic flashing
	if (delay.getElapsedTime().asMilliseconds() < 50.f)
	{
		m_pic.setColor(sf::Color(255,255,255,33)); // set sonic pic transpernt after a hit
	}
	else
	{
		m_pic.setColor(sf::Color::White); // undo the sonic pic transpernt 
		delay.restart();
	}

}

// set m_hit 
void Sonic::SetHit(bool hit)
{
	m_hit = hit;
	m_HitClock.restart();

}

// this function in charge of making sonic flash for a short period of time
void Sonic::InStrike()
{
	if (m_hit && m_HitClock.getElapsedTime().asMilliseconds() < 500.f) 
	{
		strike();
	}
	else if (m_HitClock.getElapsedTime().asMilliseconds() > 500.f)
	{
		m_hit = false;
		m_pic.setColor(sf::Color::White);
	}
}

// draw the picture
void Sonic::draw(sf::RenderWindow & window)
{
	m_window.draw(m_pic);
}

// get the picture
const sf::Sprite & Sonic::get_pic() const
{
	return m_pic;
}

// set sonic position
void Sonic::SetSonicPos(const sf::Vector2f & pos)
{
	m_position = pos;
	m_pic.setPosition(m_position);
}

// this function handle the input in order to switch between player states
void Sonic::HandleInput(Input input)
{
	 auto temp = m_state->handleInput(input);

	if (temp)
	{
		m_state = std::move(temp);
		m_state->enter(*this);
	}
}

// moves sonic right

void Sonic::SonicMoveRight()
{
	
	m_pic.move(500 * m_delta_time, 0); // new
}

// moves sonic left

void Sonic::SonicMoveLeft()
{
	m_pic.move(-500 * m_delta_time, 0); // new
}

// make sonic jump
void Sonic::SonicJump()
{

	m_speed_value -= m_gravity_acceleration*0.006;     // const
	m_pic.move(0, -m_speed_value);	
}

// return sonic position
sf::Vector2f Sonic::get_position() const
{
	return m_position;
}



// this function in charge of making sonic animation
void Sonic::animate()
{
	m_pic.setColor(sf::Color::White);
	
	if (m_while_jump)
	{
	
		if (m_clock.getElapsedTime().asSeconds() > 0.1)
		{
			if (m_index_jump_animation < m_jumping_animation.size() - 1)
				m_index_jump_animation++;
			else
				m_index_jump_animation = 0;

			m_pic.setTexture(*m_jumping_animation[m_index_jump_animation]);
			if (!faceright)
				m_pic.scale(-1.f, 1.f);

			m_clock.restart();

		}
	}
	

	if (m_clock.getElapsedTime().asSeconds() > 0.1)
	{
		if (m_index_animation < m_walking_animation.size() - 1)
			m_index_animation++;
		else
			m_index_animation = 0;

			m_pic.setTexture(*m_walking_animation[m_index_animation]);
		if(!faceright)
			m_pic.scale(-1.f, 1.f);
		
		m_clock.restart();

	}
}



// set previous position

void Sonic::SetPreviousPosition(sf::Vector2f prev)
{
	m_previous_pos = prev;
}

// gets previous position

sf::Vector2f Sonic::GetPreviousPosition() const
{
	return m_previous_pos;
}

// get m_mass

float Sonic::Get_Mass() const
{
	return m_mass;
}

// get m_jump_height

float Sonic::Get_JumpHeight() const
{
	return m_jump_height;
}

// set speed value

void Sonic::SetSpeedValue(float new_speed)
{
	m_speed_value = new_speed;
}

//set m_fall_speed_value

void Sonic::SetFallSpeedValue(float new_speed)
{
	m_fall_speed_value = new_speed;
}

// set face
void Sonic::set_face(bool face)
{
	faceright = face;
}


// in charge of making the gravity on sonic
void Sonic::falling()
{
	m_fall_speed_value += m_gravity_acceleration *0.006f;
	//m_fall_speed_value = 1;
	m_pic.move(0, m_fall_speed_value);
	// need set state to jump than animate()
	//auto temp = std::make_unique<JumpState>;
	//SetState(std::make_unique<JumpState> *temp);

	//m_while_jump = true;
	//animate();
}


Sonic::~Sonic()
{
}

