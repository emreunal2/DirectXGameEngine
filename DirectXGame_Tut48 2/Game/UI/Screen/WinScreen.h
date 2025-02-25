

#pragma once
#include <DX3D/All.h>
#include <sstream>

class WinScreen
{
public:
	WinScreen(Game* game);
	~WinScreen();

	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;

	Entity* m_screen = nullptr;
	Entity* m_background = nullptr;

};

