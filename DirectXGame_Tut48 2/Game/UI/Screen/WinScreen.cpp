

#include "WinScreen.h"
#include "../../MainGame.h"
#include <sstream>

WinScreen::WinScreen(Game* game) : m_game(game)
{
	auto font = game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");

	auto screen = game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/win_screen.png");
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
		image->setSize({ 0,0,649,673 });
		m_screen->getTransform()->setPosition(Vector3D(10, 10, 0));
	}



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
	auto clientSize = m_game->getDisplay()->getClientSize();

	auto image = m_background->getComponent<ImageComponent>();
	image->setSize({ 0,0,clientSize.getWidth(),clientSize.getHeight() });

	m_screen->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.getWidth() / 2.0f) - (649.0f/2.0f),
		(f32)(clientSize.getHeight() / 2.0f) - (673.0f / 2.0f),
		0
	));

	if (m_game->getInputSystem()->isKeyUp(Key::Enter))
	{
		static_cast<MainGame*>(m_game)->onLevelRestart();
	}
}



