#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "GameObject.h"
#include "Wall.h"
#include "Grass.h"
#include "Sonic.h"
#include "Ring.h"
#include "Diamond.h"
#include"Beatle.h"
#include "Crab.h"
#include "StaticGameObject.h"
#include "DynamicGameObject.h"
#include "Collectable.h"

class StageLoader
{
public:
	StageLoader();
	
	void LoadMap(const std::string & namefile, std::shared_ptr <Sonic>& m_player,
		std::vector < std::vector < std::unique_ptr<StaticGameObject> >  > * m_static_object,
		std::vector < std::unique_ptr<Enemy> > * m_enemy, sf::RenderWindow&,
		std::vector < std::unique_ptr<Collectable> >*  m_collectable);
	void DrawMap(sf::RenderWindow & window,  std::vector < std::vector < std::unique_ptr<StaticGameObject> >  > * m_static_object,
		std::vector < std::unique_ptr<Enemy> >* m_enemy, std::vector < std::unique_ptr<Collectable> >*  m_collectable);
	int GetNumRows() const;
	int GetNumCols() const;
	int GetLevelDiamonds() const;
	~StageLoader();

private:
	
	
	int m_level_diamonds;

	int m_stage_x, //(y) cols
		m_stage_y; //(x) rows
	sf::Sprite m_background;
};

