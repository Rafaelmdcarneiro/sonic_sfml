#include "JumpState.h"
#include "Sonic.h"



JumpState::JumpState()
{
}

std::unique_ptr<SonicState> JumpState::handleInput(Input input)
{
	// according the state diagram


	switch (input)
	{
	case PRESS_SPACE:
		return std::make_unique<JumpState>();
		break;
	case END_OF_TIMER:
		return std::make_unique<StandingState>();
		break;

	default:
		return std::make_unique<JumpState>();
		break;
	}



}

// this function in charge of loading the correct picture according the state
// and move sonic

void JumpState::enter(Sonic & player)
{

	player.SonicJump();
	player.animate();
}

