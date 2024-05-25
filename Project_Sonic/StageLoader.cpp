#include "StageLoader.h"



StageLoader::StageLoader()
	:m_level_diamonds(0)
{}


// this function gets the sonic, the enemies, the window, static objets and collectable and fill them
// according the file

void StageLoader::LoadMap(const std::string & namefile, std::shared_ptr <Sonic>& m_player, 
	std::vector < std::vector < std::unique_ptr<StaticGameObject> >  > * m_static_object,
	std::vector < std::unique_ptr<Enemy> > * m_enemy, sf::RenderWindow& window,
	std::vector < std::unique_ptr<Collectable> >*  m_collectable)
{
	m_level_diamonds = 0;
	std::ifstream inp;
	int num_object;
	char current;

	inp.open(namefile);
	if (inp.is_open()) // open in function
	{
		inp >> m_stage_y >> m_stage_x; // add the size of the window
		std::string temp; // for the first '\n'
		std::getline(inp, temp);
	}
	m_static_object->resize(m_stage_y);
	
	for (int i = 0; i < m_stage_y && !inp.eof(); i++)
	{
		std::string temp; // in order to save line from the file
		std::getline(inp, temp);
		if (temp.empty())
			m_static_object->at(i).resize(m_stage_x);

		else {
			for (int j = 0; j < m_stage_x && j < temp.size(); j++)
			{
				num_object = temp[j] - '0'; 
				switch (num_object)
				{
				case 0:
					m_static_object->at(i).emplace_back(FactoryStatic::create("Wall",sf::Vector2f(j * 32, i * 32)));
					break;
				case 1:
					m_static_object->at(i).emplace_back(FactoryStatic::create("Grass",sf::Vector2f(j * 32, i * 32)));
					break;
				case 4 :
					m_player->SetSonicPos( sf::Vector2f(j * 32, i * 32));
					break;
				case 5:
					m_enemy->emplace_back(FactoryEnemy::create("Crab", sf::Vector2f(j * 32, i * 32), window));
					break;
				case 6:
					m_enemy->emplace_back(FactoryEnemy::create("Beatle", sf::Vector2f(j * 32, i * 32), window));
					break;
				case 7 :
					m_collectable->emplace_back(std::make_unique<Ring>(sf::Vector2f(j * 32, i * 32)));               
					break;
				case 8:
					m_collectable->emplace_back(std::make_unique<Diamond>(sf::Vector2f(j * 32, i * 32)));
					m_level_diamonds++;
					break;
				case 9:
					m_enemy->emplace_back(FactoryEnemy::create("Boss", sf::Vector2f(j * 32, i * 32), window));
					break;
				default:
					m_static_object->at(i).emplace_back(nullptr);
					break;
				}
			}
			
			if(temp.size() < m_stage_x)
				m_static_object->at(i).resize(m_stage_x);

		}
	}
	
}

// this function draw the game map
void StageLoader::DrawMap(sf::RenderWindow & window, std::vector < std::vector < std::unique_ptr<StaticGameObject> >  > * m_static_object,
	std::vector < std::unique_ptr<Enemy> >* m_enemy, std::vector < std::unique_ptr<Collectable> >*  m_collectable)
{
	m_background.setTexture(ResourceManager::instance().GetTexture(BACKGROUND));
	window.draw(m_background); // draw background
	for (auto &y : *m_static_object) // draw static objects
		for (auto &x : y)
			if (x != nullptr)
				x->draw(window);

	for (auto &y : *m_enemy) // draw enemies
		if (y != nullptr)
			y->draw(window);


	for (auto &y : *m_collectable) // draw collectable objects
		if (y != nullptr)
			y->draw(window);
}



// this function gets the number of rows in the file
int StageLoader::GetNumRows() const
{
	return m_stage_y;
}

// this function gets the number of cols in the file
int StageLoader::GetNumCols() const
{
	return m_stage_x;
}

// this function gets the number of diamonds e
int StageLoader::GetLevelDiamonds() const
{
	return m_level_diamonds;
}

StageLoader::~StageLoader()
{
}
