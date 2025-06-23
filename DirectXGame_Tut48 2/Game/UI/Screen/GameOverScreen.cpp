

#include "GameOverScreen.h"
#include <sstream>
#include "../../MainGame.h"

GameOverScreen::GameOverScreen(Game* game) : m_game(game)
{

}

GameOverScreen::~GameOverScreen()
{
	try {
		m_background->release();
		m_screen->release();
	}
	catch (...) {
	}
}

void GameOverScreen::onUpdate(f32 deltaTime)
{
	auto lastDeltaTime = deltaTime;
}



