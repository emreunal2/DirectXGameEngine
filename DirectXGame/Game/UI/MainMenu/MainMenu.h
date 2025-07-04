

#pragma once
#include <DX3D/All.h>
#include <sstream>

class MainMenu
{
public:
	MainMenu(Game* game);
	~MainMenu();

	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;
	Entity* m_description = nullptr;
	Entity* m_sphereEntity = nullptr;
	f32 m_angle = 0;
};

