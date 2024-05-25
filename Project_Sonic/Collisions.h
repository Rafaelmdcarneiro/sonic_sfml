#pragma once
#include <map>
#include "GameObject.h"
#include "Sonic.h"
#include "Wall.h"
#include "Grass.h"
#include <iostream>
#include "GameStatus.h"
#include "Boss.h"
#include <exception>

class GameObject;
class Sonic;
class Wall;
class Grass;
class Spikes;

//-------------------------typedf-----------------------------------------
using HitFunctionPtr = void(*)(GameObject&, GameObject&);
using Key = std::pair<std::string, std::string >;
using HitMap = std::map<Key, HitFunctionPtr>;

//------------------------------protypes-------------------------------

void sonic_vs_wall(GameObject & sonic, GameObject& wall);
void sonic_vs_grass(GameObject & sonic, GameObject & grass);
void sonic_vs_crab(GameObject & sonic, GameObject & crab);
void sonic_vs_beatle(GameObject & sonic, GameObject & beatle);
void sonic_vs_diamond(GameObject & sonic, GameObject & diamond);
void sonic_vs_ring(GameObject & sonic, GameObject & ring);
void beatle_vs_wall(GameObject & beatle, GameObject & wall);
void crab_vs_wall(GameObject & crab, GameObject & wall);
void crab_vs_grass(GameObject & crab, GameObject & grass);
void beatle_vs_grass(GameObject & beatle, GameObject & grass);

void wall_vs_sonic(GameObject & wall, GameObject & sonic);
void grass_vs_sonic(GameObject & grass, GameObject & sonic);
void crab_vs_sonic(GameObject & crab, GameObject & sonic);
void beatle_vs_sonic(GameObject & beatle, GameObject & sonic);
void ring_vs_sonic(GameObject & ring, GameObject & sonic);
void diamond_vs_sonic(GameObject & diamond, GameObject & sonic);
void wall_vs_crab(GameObject & wall, GameObject & crab);
void wall_vs_beatle(GameObject & wall, GameObject & beatle);
void grass_vs_crab(GameObject & grass, GameObject & crab);
void grass_vs_beatle(GameObject & grass, GameObject & beatle);

void boss_vs_grass(GameObject & boss, GameObject & grass);
void grass_vs_boss(GameObject & grass, GameObject & boss);
void boss_vs_wall(GameObject & boss, GameObject & wall);
void wall_vs_boss(GameObject & wall, GameObject & boss);
void boss_vs_sonic(GameObject & boss, GameObject & sonic);
void sonic_vs_boss(GameObject & sonic, GameObject & boss);

void processCollision(GameObject& object1, GameObject& object2);
bool collide_with(GameObject& a, GameObject& b);

HitMap  initializeCollisionMap();
HitFunctionPtr lookup(const std::string& class1, const std::string& class2);

//-----------------------------------------------------------------------------

// this function lookup for collison function between two string which represent objects
HitFunctionPtr lookup(const std::string& class1, const std::string& class2)
{
	static HitMap collisionMap = initializeCollisionMap();
	auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
	if (mapEntry == collisionMap.end())
	{
		return nullptr;
	}
	return mapEntry->second;
}


// this function handle the collision between two game objects
void processCollision(GameObject& object1, GameObject& object2)
{

	auto phf = lookup(typeid(object1).name(), typeid(object2).name());
	if (!phf)
	{
		throw std::runtime_error("no collision function for the objects");
	}
	phf(object1, object2);

}



void beatle_vs_wall(GameObject & beatle, GameObject & wall)
{
	wall_vs_beatle(wall, beatle);

}


void crab_vs_wall(GameObject & crab, GameObject & wall)
{
	wall_vs_crab(wall, crab);

}

void crab_vs_grass(GameObject & crab, GameObject & grass)
{

	grass_vs_crab(grass, crab);
}

void beatle_vs_grass(GameObject & beatle, GameObject & grass)
{

	grass_vs_beatle(grass, beatle);
}



void sonic_vs_diamond(GameObject & sonic, GameObject & diamond)
{

	diamond_vs_sonic(diamond, sonic);

}


void sonic_vs_ring(GameObject & sonic, GameObject & ring)
{
	ring_vs_sonic(ring, sonic);
}


void sonic_vs_beatle(GameObject & sonic, GameObject & beatle)
{
	beatle_vs_sonic(beatle, sonic);
}

void sonic_vs_crab(GameObject & sonic, GameObject & crab)
{
	crab_vs_sonic(crab, sonic);
}

void sonic_vs_wall(GameObject & sonic, GameObject & wall)
{
	wall_vs_sonic(wall, sonic);
}

void sonic_vs_grass(GameObject & sonic, GameObject & grass)
{
	grass_vs_sonic(grass, sonic);
}


void wall_vs_sonic(GameObject & wall, GameObject & sonic)
{

	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	the_sonic.SetSonicPos(the_sonic.GetPreviousPosition()); // replacing sonic to previous position
}

void grass_vs_sonic(GameObject & grass, GameObject & sonic)
{
	
	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	the_sonic.SetSonicPos(the_sonic.GetPreviousPosition()); // replacing sonic to previous position

}


void crab_vs_sonic(GameObject & crab, GameObject & sonic)
{
	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	Crab & the_carb = dynamic_cast<Crab &>(crab);

	if (the_sonic.GetWhileJump()) // check if in jump state
	{
		the_carb.SetLife(0);
	}
	else if(!the_sonic.GetHit()) // in order to make sonic flashing awhen get hit
	{
		the_sonic.SetLife(the_sonic.GetLife()-1); 
		the_sonic.SetHit(true);
	}
}

void beatle_vs_sonic(GameObject & beatle, GameObject & sonic)
{
	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	Beatle & the_beatle = dynamic_cast<Beatle &>(beatle);

	if (the_sonic.GetWhileJump())// check if in jump state
	{
		the_beatle.SetLife(0);
	}
	else if(!the_sonic.GetHit())
	{
		the_sonic.SetLife(the_sonic.GetLife() - 1); 
		the_sonic.SetHit(true);
	}
}


void ring_vs_sonic(GameObject & ring, GameObject & sonic)
{
	
	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	the_sonic.SetScore(the_sonic.GetScore()+100); // collision with ring gives the player score

	
}


void diamond_vs_sonic(GameObject & diamond, GameObject & sonic)
{
	
	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	the_sonic.SetEatenDiamonds(the_sonic.GetEatenDiamonds()+1);
	the_sonic.SetScore(the_sonic.GetScore() + 1000); // collision with diamons gives the player score
}

void wall_vs_crab(GameObject & wall, GameObject & crab)
{
	Crab & the_carb = dynamic_cast<Crab &>(crab);
	the_carb.SetPosition(the_carb.GetPreviousPos());


}

void wall_vs_beatle(GameObject & wall, GameObject & beatle)
{
	Beatle & the_beatle = dynamic_cast<Beatle &>(beatle);
	the_beatle.SetPosition(the_beatle.GetPreviousPos()); // relocate beatle to previous position

}

void grass_vs_crab(GameObject & grass, GameObject & crab)
{
	Crab & the_carb = dynamic_cast<Crab &>(crab);
	the_carb.SetPosition(the_carb.GetPreviousPos());  // relocate crab to previous position

}

void grass_vs_beatle(GameObject & grass, GameObject & beatle)
{
	Beatle & the_beatle = dynamic_cast<Beatle &>(beatle);
	the_beatle.SetPosition(the_beatle.GetPreviousPos()); // relocate beatle to previous position

}

void boss_vs_grass(GameObject & boss, GameObject & grass)
{
	grass_vs_boss(grass, boss);
}

void grass_vs_boss(GameObject & grass, GameObject & boss)
{
	
}

void boss_vs_wall(GameObject & boss, GameObject & wall)
{
	wall_vs_boss(wall, boss);
}

void wall_vs_boss(GameObject & wall, GameObject & boss)
{
	
}

void boss_vs_sonic(GameObject & boss, GameObject & sonic)
{
	sonic_vs_boss(sonic, boss);
}

void sonic_vs_boss(GameObject & sonic, GameObject & boss)
{
	Sonic & the_sonic = dynamic_cast<Sonic &>(sonic);
	Boss & the_beatle = dynamic_cast<Boss &>(boss);

	if (the_sonic.GetWhileJump())// check if in jump state
	{
		the_beatle.SetLife(0);
	}
	else if (!the_sonic.GetHit())
	{
		the_sonic.SetLife(the_sonic.GetLife() - 1);
		the_sonic.SetHit(true);
	}
}

//initlize map

HitMap  initializeCollisionMap()
{
	HitMap phm;
	phm[Key(typeid(Wall).name(), typeid(Sonic).name())] = &wall_vs_sonic;
	phm[Key(typeid(Grass).name(), typeid(Sonic).name())] = &grass_vs_sonic;
	phm[Key(typeid(Sonic).name(), typeid(Wall).name())] = &sonic_vs_wall;
	phm[Key(typeid(Sonic).name(), typeid(Grass).name())] = &sonic_vs_grass;
	phm[Key(typeid(Sonic).name(), typeid(Crab).name())] = &sonic_vs_crab;
	phm[Key(typeid(Crab).name(), typeid(Sonic).name())] = &crab_vs_sonic;
	phm[Key(typeid(Sonic).name(), typeid(Beatle).name())] = &sonic_vs_beatle;
	phm[Key(typeid(Beatle).name(), typeid(Sonic).name())] = &beatle_vs_sonic;
	phm[Key(typeid(Ring).name(), typeid(Sonic).name())] = &ring_vs_sonic;
	phm[Key(typeid(Sonic).name(), typeid(Ring).name())] = &sonic_vs_ring;
	phm[Key(typeid(Sonic).name(), typeid(Diamond).name())] = &sonic_vs_diamond;
	phm[Key(typeid(Diamond).name(), typeid(Sonic).name())] = &diamond_vs_sonic;
	phm[Key(typeid(Crab).name(), typeid(Wall).name())] = &crab_vs_wall;
	phm[Key(typeid(Wall).name(), typeid(Crab).name())] = &wall_vs_crab;
	phm[Key(typeid(Beatle).name(), typeid(Wall).name())] = &beatle_vs_wall;
	phm[Key(typeid(Wall).name(), typeid(Beatle).name())] = &wall_vs_beatle;
	phm[Key(typeid(Crab).name(), typeid(Grass).name())] = &crab_vs_grass;
	phm[Key(typeid(Grass).name(), typeid(Crab).name())] = &grass_vs_crab;
	phm[Key(typeid(Beatle).name(), typeid(Grass).name())] = &beatle_vs_grass;
	phm[Key(typeid(Grass).name(), typeid(Beatle).name())] = &grass_vs_beatle;
	phm[Key(typeid(Boss).name(), typeid(Grass).name())] = &boss_vs_grass;
	phm[Key(typeid(Grass).name(), typeid(Boss).name())] = &grass_vs_boss;
	phm[Key(typeid(Boss).name(), typeid(Wall).name())] = &boss_vs_wall;
	phm[Key(typeid(Wall).name(), typeid(Boss).name())] = &wall_vs_boss;
	phm[Key(typeid(Boss).name(), typeid(Sonic).name())] = &boss_vs_sonic;
	phm[Key(typeid(Sonic).name(), typeid(Boss).name())] = &sonic_vs_boss;
	return phm;
}

// this function gets to game object and check if they overlap
bool collide_with(GameObject& a, GameObject& b)
{
	sf::FloatRect charater = a.get_pic().getGlobalBounds();
	sf::FloatRect wallRect = b.get_pic().getGlobalBounds();

	if (charater.left < (wallRect.left + wallRect.width) && charater.top < (wallRect.top + wallRect.height) &&
		wallRect.left < (charater.left + charater.width) && wallRect.top < (charater.top + charater.height))
	{
		return true;
	}
	return false;
}
