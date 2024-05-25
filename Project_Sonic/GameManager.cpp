#include "GameManager.h"
#include "Collisions.h"

GameManager::GameManager(int width, int height, std::string game_title)
	:m_player(std::make_shared<Sonic>(sf::Vector2f(0,0), m_window)) , m_static_object(), m_enemy() , m_level_num(1),
	m_dead_enemy()
{
	m_window.create(sf::VideoMode (width, height), game_title);
	m_sound_track.setBuffer(ResourceManager::instance().GetAudio(SOUND_TRACK));
	m_sound_track.setLoop(true);
	m_eat_sound.setBuffer(ResourceManager::instance().GetAudio(EAT_SOUND));
	m_strike.setBuffer((ResourceManager::instance().GetAudio(SONIC_KILL_SOUND)));
	m_sonic_death.setBuffer(ResourceManager::instance().GetAudio(SONIC_DEATH_SOUND));
}

// this function in charge of running the game
void GameManager::run()
{
	float zoomFactor = 1.2f;
	sf::Vector2f centerOfView;
	bool want_to_play; // data member
	want_to_play = m_menu.start(m_window); // first menu   

	while (want_to_play)  //new2
	{
		m_window.create(sf::VideoMode(900, 700), "Sonic"); // setting thw window
		m_sound_track.play();
		load_level(); 
		centerOfView = { m_player->get_pic().getPosition() }; // set center of view

		game_clock.restart();

		while (m_window.isOpen())
		{
			// check if the player end the level
			if (m_player->GetEatenDiamonds() == m_map.GetLevelDiamonds() && m_map.GetLevelDiamonds() != 0)
			{
				if (m_level_num == 3) // max levels
					want_to_play = m_menu.win(m_window);
				else
				{
					m_player->SetLife(m_player->GetLife() + 3);
					load_level();
				}
			}
			
			float d_time = game_clock.restart().asSeconds();
			SetDynamicTime(d_time); // send the time in order to move the dynamics according the game clock
			m_window.clear();
			m_map.DrawMap(m_window, &m_static_object, &m_enemy, &m_collectable);
			m_window.draw(m_player->get_pic());
			
			sf::Vector2f position = MakeCenterToView(); // hof
			sf::View view(position, sf::Vector2f(m_window.getSize().x / 1.5, m_window.getSize().y / 1.5)); // change to data member
			
			view.zoom(zoomFactor);
			
			m_window.setView(view);
			m_status.draw(m_player, m_window, view.getCenter(), m_map.GetLevelDiamonds(), m_level_num-1);
			m_window.display();

			if (!m_player->GetWhileJump()) // turn on gravity when the player not jumping
				if (!DownCollision()) // check if the player dont collide with the floor
					m_player->falling();
					
			sf::Event event;
			while (m_window.pollEvent(event))
			{
			  switch (event.type)
			  {
				case sf::Event::EventType::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape: // open pause menu
						want_to_play = m_menu.suspend(m_window);
						if (want_to_play)  //new2
							m_window.create(sf::VideoMode(900, 700), "Sonic");
						break;
					}
					break;
				case sf::Event::EventType::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Left:
						m_player->HandleInput(RELEASE_LEFT);
						break;
					case sf::Keyboard::Right:
						m_player->HandleInput(RELEASE_RIGHT);
						break;
					}
				}

			}

			for (auto& itr : m_enemy)
			{
				if (itr != nullptr)
				{
					itr->animate(); // doing the animation of the enemies
					itr->update(m_player->get_pic().getPosition()); // move the enemies
					CheckCollideEnemyAndStatic(); // check if enemy and static object collide
					CheckCollideEnemy(); // check collide between enemy and sonic
				}
			}

			if (m_time_explosion.getElapsedTime().asSeconds() < 0.3f)
				Explode(view); // making the explosion 
			else
				m_dead_enemy.clear(); // empty the vecetor for not presenting two explosions at the same time

			CheckCollideCollectable(); // check if the playercollide with ring and diamonds

			if (m_player->GetWhileJump()) // check if the player still in jump state
				Jumping(view); // making the jumping
			else
			{
				m_player->SetPreviousPosition(m_player->get_pic().getPosition());
				HandleInput(); // does the movement of the player
			}
				
			
			if (m_player->GetLife() <= 0) // if the player lost the game
				want_to_play = m_menu.lose(m_window);
		}
	}	
}

// handle the user input
void GameManager::HandleInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player->HandleInput(PRESS_RIGHT);
		RightCollision(); // check collision in the right side
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player->HandleInput(PRESS_LEFT);
		LeftCollision();// check collision in the left side
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && DownCollision() )
	{
		
		m_player->SetSpeedValue(m_player->Get_JumpHeight() / m_player->Get_Mass()); // calculate the jump
		m_player->SetWhileJump(true); 
		m_player->HandleInput(PRESS_SPACE);
		UpCollision(); // check collision in the up side
	}
	
	if(!m_player->GetWhileJump())
		m_player->InStrike(); // make the player flashing
	
	m_player->SetFallSpeedValue(1.5f); // hof
}

// check collision with  the buttom static objects
bool GameManager::DownCollision()
{
	
	float m_row = (m_player->get_pic().getPosition().y / 32.f);
	float m_col = (m_player->get_pic().getPosition().x / 32.f);

 	int row = int(m_row+0.5 );
	int col = ceil(m_col - 1);

		for (int j = col - 1; j < col + 3 && j >-1 && j < m_static_object[row + 1].size(); j++)
			if (m_static_object[row + 1][j] != nullptr)
				if (collide_with(*m_player, *m_static_object[row + 1][j]))
					return true;

		return false;
}
	
// check collision with upper static objects
void GameManager::UpCollision()
{
	
	float m_row = m_player->get_pic().getPosition().y / 32.f;
	float m_col = m_player->get_pic().getPosition().x / 32.f;

	int row = int(m_row + 0.5);
	int col = ceil(m_col - 1);

	for (int j = col - 3; j < col + 3 && j >-1 && j < m_static_object[row - 1].size(); j++)
		if (m_static_object[row - 1][j] != nullptr)
		{
			if (collide_with(*m_player, *m_static_object[row - 1][j]))
				processCollision(*m_player, *m_static_object[row - 1][j]);
		}		
}

// // check collision with right side static objects
void GameManager::RightCollision()
{
	
	float m_row = m_player->get_pic().getPosition().y / 32.f;
	float m_col = m_player->get_pic().getPosition().x / 32.f;

	int row = int(m_row + 0.5);
	int col = ceil(m_col - 1);
	
	for (int j = col -2; j < col +5 && j < m_static_object[row].size() && j >-1; j++)
		if (m_static_object[row][j] != nullptr)
		{
			if (collide_with(*m_player, *m_static_object[row][j]))
			{
				processCollision(*m_player, *m_static_object[row][j]);
				
			}
		}
	
}

// check collision with left side static objects
void GameManager::LeftCollision()
{
	
	float m_row = m_player->get_pic().getPosition().y / 32.f;
	float m_col = m_player->get_pic().getPosition().x / 32.f;

	int row = int(m_row + 0.5);
	int col = floor(m_col);

	if (col < 5)
		col = 5;
	
  	for(int j = col-5; j < col+1 && j < m_static_object[row].size() && j >-1;j++)
		if (m_static_object[row][j] != nullptr)
		{
			if (collide_with(*m_player, *m_static_object[row][j]))
			{
				processCollision(*m_player, *m_static_object[row][j]);
				
			}
		}
	
}

// create center for the view 

sf::Vector2f GameManager::MakeCenterToView()
{
	sf::Vector2f pos = m_player->get_pic().getPosition();
	int num_cols = m_map.GetNumCols(),
		num_rows = m_map.GetNumRows();

	if (pos.x < 350)
		pos.x = 350;
	if (pos.x >(num_cols * 32 - 412)) // 412
		pos.x = (num_cols * 32 - 412);
	if (pos.y < 268)
		pos.y = 268;
	if (pos.y >(num_rows * 32 - 266))
		pos.y = (num_rows * 32 - 266);

	return pos;
}

// sending the game time to all dynamics objects
void GameManager::SetDynamicTime(float time)
{
	m_player->set_delta_time(time);// new
	for (auto& itr : m_enemy)
	{
		if (itr != nullptr)
			itr->SetDelta(time);
	}

}

// this function managing the player jumping
void GameManager::Jumping(sf::View & view)
{
	m_window.clear();
	m_map.DrawMap(m_window, &m_static_object, &m_enemy, &m_collectable);
	m_window.draw(m_player->get_pic());
	m_status.draw(m_player, m_window, view.getCenter(), m_map.GetLevelDiamonds(), m_level_num - 1);
	m_window.display();

	m_player->SetPreviousPosition(m_player->get_pic().getPosition());
	m_player->move_in_jump();
	RightCollision();
	LeftCollision();

		

	m_player->HandleInput(PRESS_SPACE);

	// check collide with static objects
	for (auto &x : (m_static_object))
	{
		for (auto &y : x)
			if (y != nullptr)
				if (collide_with(*m_player, *y))
				{
					m_player->SetWhileJump(false);
					m_player->HandleInput(END_OF_TIMER);
					break;
				}
		if (!m_player->GetWhileJump())
			break;
	}

}

// chack collide with diamonds and rings
void GameManager::CheckCollideCollectable()
{
	for (auto& itr : m_collectable)
	{
		if (itr != nullptr)
		{

			if (collide_with(*m_player, *itr))
			{
				m_eat_sound.play();
				processCollision(*m_player, *itr);
				m_collectable.erase(std::remove(m_collectable.begin(), m_collectable.end(), itr), m_collectable.end());
			}
		}
	}
}

// check collide with the enemies
void GameManager::CheckCollideEnemy()
{
	for (auto& itr : m_enemy)
	{
		if (itr != nullptr)
		{
			if (collide_with(*m_player, *itr))
			{
				if (m_player->GetWhileJump())
				{
					processCollision(*m_player, *itr);
					m_dead_enemy.emplace_back(std::move(itr));
					m_time_explosion.restart();
				}
				else
				{
					m_sound_track.pause();
					m_sonic_death.play();
					m_sound_track.play();
					processCollision(*m_player, *itr);
				}
			}
		}
	}
}

// check collide between enemies ans static
void GameManager::CheckCollideEnemyAndStatic()
{

	for (auto &itr : m_enemy)
	{
		if (itr != nullptr)
		{
			float m_row = itr->get_pic().getPosition().y / 32.f;
			float m_col = itr->get_pic().getPosition().x / 32.f;

			int row = int(m_row + 0.5);
			int col = ceil(m_col - 1);

			for (int j = col - 1; j < col + 5 && j < m_static_object[row].size() && j >-1; j++)
				if (m_static_object[row][j] != nullptr)
				{
					if (collide_with(*itr, *m_static_object[row][j]))
					{
						processCollision(*itr, *m_static_object[row][j]);
					}
				}

			m_row = itr->get_pic().getPosition().y / 32.f;
			m_col = itr->get_pic().getPosition().x / 32.f;

			row = int(m_row + 0.5);
			col = floor(m_col);

			if (col < 5)
				col = 5;

			for (int j = col - 5; j < col + 1 && j < m_static_object[row].size() && j >-1; j++)
				if (m_static_object[row][j] != nullptr)
				{
					if (collide_with(*itr, *m_static_object[row][j]))
					{
						processCollision(*itr, *m_static_object[row][j]);

					}
				}
		}
	}
}

// making the explosion picture of the collisions
void GameManager::Explode(sf::View& view)
{
	for (auto& itr : m_dead_enemy)
	{
		if (itr != nullptr)
		{
			itr->explosion();
			m_strike.play();
			m_window.clear();
			m_map.DrawMap(m_window, &m_static_object, &m_enemy, &m_collectable);
			m_window.draw(m_player->get_pic());
			itr->draw(m_window);
			m_status.draw(m_player, m_window, view.getCenter(), m_map.GetLevelDiamonds(), m_level_num - 1);
			m_window.display();
		}
	}
}


// this function in charge of loading the game levels
void GameManager::load_level()
{
	m_static_object.clear();
	m_collectable.clear();
	m_enemy.clear();
	m_player->SetEatenDiamonds(0);
	std::string level_name = "level" + std::to_string(m_level_num) + ".txt";
	m_map.LoadMap(level_name, m_player, &m_static_object, &m_enemy, m_window, &m_collectable);
	m_level_num++;
}

GameManager::~GameManager()
{
}
