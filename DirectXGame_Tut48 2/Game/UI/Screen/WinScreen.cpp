

#include "WinScreen.h"
#include "../../MainGame.h"
#include <sstream>

WinScreen::WinScreen(Game* game) : m_game(game)
{

}

WinScreen::~WinScreen()
{
	try {
		m_background->release();
		m_screen->release();
	}
	catch(...) {
		// Handle any exceptions that may occur during release
	}
}

void WinScreen::onUpdate(f32 deltaTime)
{
	auto dummy = deltaTime;
}



