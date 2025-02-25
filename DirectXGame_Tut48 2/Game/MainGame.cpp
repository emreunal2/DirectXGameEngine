/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "MainGame.h"
#include "Item/Spaceship.h"
#include "Item/BoxItem.h"
#include "Item/AsteroidItem.h"
#include <time.h>


MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}




void MainGame::onCreate()
{
	Game::onCreate();
	
	this->getDisplay()->setFullScreen(this->getDisplay()->getScreenSize(), true);
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
