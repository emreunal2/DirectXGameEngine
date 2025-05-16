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
	void CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass);
	void CreateStaticSphere(f32 radius, f32 lenght, f32 posx, f32 posy, f32 posz);
	void CreateStaticCube(f32 size, f32 posx, f32 posy, f32 posz);
private:
	Game* m_game = nullptr;

};

