#include "WalkLeftState.h"
#include "Sonic.h"



WalkLeftState::WalkLeftState()
{
}


std::unique_ptr<SonicState> WalkLeftState::handleInput(Input input)
{
	// according the state diagram

	switch (input)
	{
	case PRESS_SPACE:
		return std::make_unique<JumpState>();
		break;
	case PRESS_LEFT:
		return std::make_unique<WalkLeftState>();
		break;
	case RELEASE_LEFT:
		return std::make_unique<StandingState>();
		break;
	default:
		return std::make_unique<WalkLeftState>();
		break;
	}


}

// this function in charge of loading the correct picture according the state
// and move sonic
void WalkLeftState::enter(Sonic & player)
{
	
	player.SonicMoveLeft();
	player.flip_pic_left();
	player.animate();
}

