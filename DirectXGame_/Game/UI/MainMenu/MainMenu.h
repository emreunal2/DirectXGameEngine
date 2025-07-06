

#pragma once
#include <DX3D/All.h>
#include <sstream>

class MainMenu
{
public:
	explicit MainMenu(Game* game);
	~MainMenu();
	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;
	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;
	Entity* m_description = nullptr;
	Entity* m_sphereEntity = nullptr;
	f32 m_angle = 0;
	Entity* m_sphere = nullptr;
	Entity* m_lightEntity = nullptr;
};

