

#include "MainGame.h"


i32 main()
{
	try
	{
		MainGame game;
		game.run();
	}
	catch (...) 
	{
		return -1;
	}

	return 0;
}