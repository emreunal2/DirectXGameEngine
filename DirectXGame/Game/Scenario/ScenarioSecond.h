#pragma once
#include <DX3D/All.h>
#include <sstream>
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"
#include "../Item/StaticCubeItem.h"

class ScenarioSecond
{
public:
	ScenarioSecond(Game* game);
	~ScenarioSecond();
	void generateScenario();
	void onRestart();
	void onCreate();
	void onUpdate(f32 deltaTime);
	void CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass, MaterialType type);
	void CreateStaticSphere(f32 radius, f32 lenght, f32 posx, f32 posy, f32 posz);
	void CreateStaticCube(f32 sizex, f32 sizey, f32 sizez, f32 posx, f32 posy, f32 posz);
private:
	Game* m_game = nullptr;
	float m_spawnTimer = 0.0f;
	float m_spawnInterval = 1.0f; // time between spawns (in seconds)
	int m_spawnedCount = 0;
	int m_maxSpheres = 100;
};

