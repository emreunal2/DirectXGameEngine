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

#include "GameOverScreen.h"
#include <sstream>
#include "../../MainGame.h"

GameOverScreen::GameOverScreen(Game* game) : m_game(game)
{
	auto font = game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");

	auto screen = game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/gameover_screen.png");
	auto background = game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/screen_background.png");

	{
		m_background = game->getWorld()->createEntity<Entity>();
		auto image = m_background->createComponent<ImageComponent>();
		image->setImage(background);
		image->setSize({ 0,0,0,0 });
		m_background->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_screen = game->getWorld()->createEntity<Entity>();
		auto image = m_screen->createComponent<ImageComponent>();
		image->setImage(screen);
		image->setSize({ 0,0,649,706 });
		m_screen->getTransform()->setPosition(Vector3D(10, 10, 0));
	}
}

GameOverScreen::~GameOverScreen()
{
	m_background->release();
	m_screen->release();
}

void GameOverScreen::onUpdate(f32 deltaTime)
{
	auto clientSize = m_game->getDisplay()->getClientSize();

	auto image = m_background->getComponent<ImageComponent>();
	image->setSize({ 0,0,clientSize.width,clientSize.height });

	m_screen->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.width / 2.0f) - (649.0f / 2.0f),
		(f32)(clientSize.height / 2.0f) - (706.0f / 2.0f),
		0
	));

	if (m_game->getInputSystem()->isKeyUp(Key::Enter))
	{
		static_cast<MainGame*>(m_game)->onLevelRestart();
	}

}



