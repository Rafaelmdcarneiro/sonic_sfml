#include <SFML/Graphics.hpp>
#include "GameManager.h"


#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#else
#pragma comment(lib, "sfml-main.lib")
#endif


int main()
{
	GameManager game (900,700,"Sonic");
	game.run();


	return 0;
}

