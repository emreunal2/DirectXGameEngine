#pragma once
#include <DX3D/All.h>
#include <sstream>


class ScenarioMainMenu
{
public:
	ScenarioMainMenu(Game* game);
	~ScenarioMainMenu();

	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);

private:
	Game* m_game = nullptr;
};

