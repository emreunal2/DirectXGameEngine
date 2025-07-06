#include "ImGUIManager.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "../MainSimulation.h"

#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/GraphicsEngine.h>

ImGUIManager::ImGUIManager(MainSimulation* game) : m_game(game)
{

}

ImGUIManager::~ImGUIManager()
{

}
void ImGUIManager::beginFrame()
{
	ImGui::SetCurrentContext(ImGui::GetCurrentContext());
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGUIManager::endFrame()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGUIManager::render()
{
	ImGui::Begin("Game Menu");
	ImGui::Text("Game Menu");
	ImGui::End();
}


