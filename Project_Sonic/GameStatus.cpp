#include "GameStatus.h"



GameStatus::GameStatus()
	:m_lives(5), m_score(0), m_diamonds(0)
{
}


GameStatus::~GameStatus()
{
}

// gets score 
int GameStatus::get_score()
{
	return m_score;
}
// sets score
void GameStatus::set_score(int score)
{
	m_score = score;
}
// this function in charge of preseting the game status on the screen
void GameStatus::draw(std::shared_ptr <Sonic> & sonic, sf::RenderWindow & window, sf::Vector2f center_of_view, int diamonds_in_levels, int level)
{
	sf::Vector2f UpLeftCorner;
	UpLeftCorner.y = center_of_view.y - 270;
	UpLeftCorner.x = center_of_view.x - 320;
	

	m_lives = sonic->GetLife();
	m_diamonds = sonic->GetEatenDiamonds();
	m_score = sonic->GetScore();

	std::ostringstream os_score,
		os_lives, os_diamonds;

	sf::Text game_score,
		lives,
		diamonds;

	os_score << "Level: " << level << "  Score: " << m_score;
	os_lives << "Lives: " << m_lives;
	os_diamonds << "Diamonds: " << m_diamonds <<"/" << diamonds_in_levels;

	lives.setCharacterSize(24);   
	game_score.setCharacterSize(24);
	diamonds.setCharacterSize(24);

	game_score.setPosition(UpLeftCorner);
	lives.setPosition({ UpLeftCorner.x, UpLeftCorner.y + 30 });
	diamonds.setPosition({ UpLeftCorner.x, UpLeftCorner.y + 60 });

	game_score.setFont(ResourceManager::instance().GetFont());
	lives.setFont(ResourceManager::instance().GetFont());
	diamonds.setFont(ResourceManager::instance().GetFont());

	game_score.setFillColor(sf::Color::Black);
	lives.setFillColor(sf::Color::Black);
	diamonds.setFillColor(sf::Color::Black);

	game_score.setString(os_score.str());
	lives.setString(os_lives.str());
	diamonds.setString(os_diamonds.str());


	window.draw(game_score);
	window.draw(lives);
	window.draw(diamonds);

}
