#pragma once
#include <DX3D/All.h>
#include <sstream>

class ScenarioFourth
{
public:
	ScenarioFourth(Game* game);
	~ScenarioFourth();
	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;
};

