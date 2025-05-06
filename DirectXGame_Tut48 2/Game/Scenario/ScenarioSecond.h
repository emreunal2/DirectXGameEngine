#pragma once
#include <DX3D/All.h>
#include <sstream>

class ScenarioSecond
{
public:
	ScenarioSecond(Game* game);
	~ScenarioSecond();
	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;
};

