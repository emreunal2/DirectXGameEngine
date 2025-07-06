

#include "MainGame.h"
#include "Item/Spaceship.h"
#include "Item/BoxItem.h"
#include "Item/AsteroidItem.h"
#include <time.h>


MainGame::MainGame() = default;

MainGame::~MainGame() = default;




void MainGame::onCreate()
{
	Game::onCreate();
	
	m_menu = std::make_unique<MainMenu>(this);
}

void MainGame::onUpdate(f32 deltaTime)
{
	Game::onUpdate(deltaTime);

	if (m_menu) m_menu->onUpdate(deltaTime);
	if (m_level) m_level->onUpdate(deltaTime);
}


void MainGame::onNewGame()
{
	m_menu.reset();

	m_level = std::make_unique<Level>(this);
	m_level->onCreate();
}

void MainGame::onLevelRestart()
{
	if (m_level) m_level->onRestart();
}

void MainGame::onReturnToMainMenu()
{
	m_level.reset();
	m_menu = std::make_unique<MainMenu>(this);
}
