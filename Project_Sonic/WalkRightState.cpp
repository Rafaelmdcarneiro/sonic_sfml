#include "WalkRightState.h"
#include "Sonic.h"



WalkRightState::WalkRightState()
{
}

std::unique_ptr<SonicState> WalkRightState::handleInput(Input input)
{
	// according the state diagram
	switch (input)
	{
	case PRESS_SPACE:
		return std::make_unique<JumpState>(); 
		break;

	case PRESS_RIGHT:
		return std::make_unique<WalkRightState>();
		break;

	case RELEASE_RIGHT:
		return std::make_unique<StandingState>();

	default:
		return std::make_unique<WalkRightState>();
		break;
	}
}

// this function in charge of loading the correct picture according the state
// and move sonic
void WalkRightState::enter(Sonic & player)
{
	player.SonicMoveRight();
	player.flip_pic_right();
	player.animate();
}

