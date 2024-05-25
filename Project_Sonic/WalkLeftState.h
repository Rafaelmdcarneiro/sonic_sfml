#pragma once
#include "SonicState.h"
#include "StandingState.h"

class Sonic;


class WalkLeftState :
	public SonicState
{
public:
	WalkLeftState();
	std::unique_ptr<SonicState> handleInput(Input input);
	void enter(Sonic& player);
	~WalkLeftState() {};
};

