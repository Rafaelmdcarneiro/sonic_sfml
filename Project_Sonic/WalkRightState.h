#pragma once
#include "SonicState.h"
#include "StandingState.h"

class Sonic;

class WalkRightState :
	public SonicState
{
public:
	WalkRightState();
	std::unique_ptr<SonicState> handleInput(Input input);
	void enter(Sonic& player);
	~WalkRightState() {};
};

