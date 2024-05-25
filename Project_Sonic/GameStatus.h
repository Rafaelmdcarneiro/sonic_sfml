#pragma once
#include "Sonic.h"
#include<sstream>
#include "ResourceManager.h"

class GameStatus
{
public:
	GameStatus();
	~GameStatus();
public:
	
	int get_score();
	void set_score(int score);
	void draw(std::shared_ptr <Sonic> &sonic, sf::RenderWindow& window, sf::Vector2f center_of_view, int diamonds_in_levels, int level);

private:
	int m_score, 
		m_lives,
		m_diamonds;
	
};

