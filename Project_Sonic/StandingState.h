#pragma once
#include "SonicState.h"
#include "WalkRightState.h"
#include "WalkLeftState.h"
#include "JumpState.h"

class Sonic;

class StandingState :
	public SonicState
{
public:
	StandingState();
	std::unique_ptr<SonicState> handleInput(Input input);
	void enter(Sonic& player);
	~StandingState() {};
};

