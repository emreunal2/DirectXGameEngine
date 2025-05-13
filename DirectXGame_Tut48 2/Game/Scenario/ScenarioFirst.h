#pragma once
#include <DX3D/All.h>
#include <sstream>

class ScenarioFirst
{
public:
	ScenarioFirst(Game* game);
	~ScenarioFirst();
	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);
	void CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz);
private:
	Game* m_game = nullptr;

};

