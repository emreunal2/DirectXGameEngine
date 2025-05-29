#pragma once
#include <DX3D/Prerequisites.h>

class MainSimulation;

class ImGUIManager
{
public:
	ImGUIManager(MainSimulation* game);
	~ImGUIManager();
	void beginFrame();
	void endFrame();
	void render();

private:
	MainSimulation* m_game = nullptr;
};

