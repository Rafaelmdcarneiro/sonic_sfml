#pragma once
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include <string>
#include <memory>
#include "StageLoader.h"
#include "Sonic.h"
#include "Collectable.h"
#include "Menu.h"
#include "GameStatus.h"

class Collisions;

class GameManager
{
public:
	GameManager(int width , int height, std::string );
	void run();
	void HandleInput();
	bool DownCollision();
	void UpCollision();
	void RightCollision();
	void LeftCollision();
	sf::Vector2f MakeCenterToView();
	void SetDynamicTime(float);
	void Jumping(sf::View &);
	void CheckCollideCollectable();
	void CheckCollideEnemy();
	void CheckCollideEnemyAndStatic();
	void Explode(sf::View & );



	void load_level();
	~GameManager();

private:
	sf::Clock game_clock; 
	sf::Clock m_time_explosion; // for the eplosion pic
	int m_level_num;
	sf::RenderWindow m_window;
	std::vector < std::vector < std::unique_ptr<StaticGameObject> > > m_static_object;
	std::vector < std::unique_ptr<Enemy> > m_enemy;
	std::vector < std::unique_ptr<Enemy> > m_dead_enemy;
	std::vector < std::unique_ptr<Collectable> > m_collectable;
	StageLoader m_map;
	std::shared_ptr <Sonic> m_player;
	Menu m_menu;
	sf::View m_view;
	// for the audio
	sf::Sound m_sound_track,
			  m_eat_sound,
			  m_strike,
			  m_sonic_death;
	GameStatus m_status; 

	
};

