#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Menu
{
public:
	Menu();
	bool main_loop(sf::RenderWindow & window, sf::Vector2f play_position, sf::Vector2f exit_position);

	bool start(sf::RenderWindow & window);
	bool win(sf::RenderWindow & window);
	bool lose(sf::RenderWindow & window);
	bool suspend(sf::RenderWindow & window);

	void draw_play_button(sf::RenderWindow & window, sf::Vector2f position);
	void draw_exit_button(sf::RenderWindow & window, sf::Vector2f position);

	~Menu();


private:
	sf::Sprite m_menu,
		m_play_button,
		m_exit_button;

	sf::Sound m_winning_menu,
		m_button_touched;
};