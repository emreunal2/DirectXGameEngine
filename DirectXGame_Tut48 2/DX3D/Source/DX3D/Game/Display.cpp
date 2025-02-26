

#include <DX3D/Game/Display.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/SwapChain.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

Display::Display(Game* game): m_game(game)
{
	auto size = getClientSize();
	m_swapChain = game->getGraphicsEngine()->getRenderSystem()->createSwapChain(static_cast<HWND>(m_hwnd), size.width, size.height);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(game->getGraphicsEngine()->getRenderSystem()->m_d3d_device.Get(), game->getGraphicsEngine()->getRenderSystem()->m_imm_context.Get());
	ImGui::StyleColorsDark();
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
