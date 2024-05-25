#pragma once
#include <memory>


class Sonic;

enum Input
{
	PRESS_UP,
	PRESS_DOWN,
	PRESS_LEFT,
	PRESS_RIGHT,
	PRESS_SPACE,
	END_OF_TIMER,
	RELEASE_DOWN,
	RELEASE_RIGHT,
	RELEASE_LEFT,
	RELEASE_UP
};


class SonicState
{
public:
	
	virtual ~SonicState() { }
	virtual std::unique_ptr<SonicState>	handleInput(Input input) = 0;
	virtual void enter(Sonic& player) = 0;
	
};

