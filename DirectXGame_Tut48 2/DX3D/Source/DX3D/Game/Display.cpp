

#include <DX3D/Game/Display.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/SwapChain.h>

Display::Display(Game* game): m_game(game)
{
	auto size = getClientSize();
	m_swapChain = game->getGraphicsEngine()->getRenderSystem()->createSwapChain(static_cast<HWND>(m_hwnd), size.width, size.height);
}

Display::~Display()
{
}

void Display::setFullScreen(const Rect& size, bool fullscreen)
{
	m_swapChain->setFullScreen(fullscreen, size.width, size.height);
}

void Display::onSize(const Rect& size)
{
	m_swapChain->resize(size.width, size.height);
	m_game->onDisplaySize(size);
}
