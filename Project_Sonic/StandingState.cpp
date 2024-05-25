#include "StandingState.h"
#include "Sonic.h"


StandingState::StandingState()
{
}



std::unique_ptr<SonicState> StandingState::handleInput(Input input) 
{
	// according the state diagram

	switch (input)
	{

	case PRESS_LEFT:
		return std::make_unique<WalkLeftState>();
		break;
	case PRESS_RIGHT:
		return std::make_unique<WalkRightState>();
		break;
	case PRESS_SPACE:
		return std::make_unique<JumpState>();
		break;

	default:
		return std::make_unique<StandingState>();
		break;
	}
}

// this function in charge of loading the correct picture according the state

void StandingState::enter(Sonic & player)
{
	player.load_stand_image();
}

