#pragma once
#include <DX3D/All.h>
#include <sstream>

class Scenario
{
public:
	Scenario(Game* game);
	~Scenario();

	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);

private:
	Game* m_game = nullptr;
	Entity* m_sphereEntity = nullptr;
	f32 m_angle = 0;
};

