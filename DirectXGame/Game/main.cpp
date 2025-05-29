

#include "MainGame.h"
#include "MainSimulation.h"

i32 main()
{
	try
	{
		MainSimulation game;
		game.run();
	}
	catch (...) 
	{
		return -1;
	}

	return 0;
}