#pragma once
#include "SonicState.h"
#include "StandingState.h"

class Sonic;

class JumpState :
	public SonicState
{
public:
	JumpState();
	std::unique_ptr<SonicState> handleInput(Input input);
	void enter(Sonic& player);
	~JumpState() {};


};

