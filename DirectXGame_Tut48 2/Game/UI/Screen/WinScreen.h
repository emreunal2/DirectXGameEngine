

#pragma once
#include <DX3D/All.h>
#include <sstream>

class WinScreen
{
public:
	explicit WinScreen(Game* game);
	~WinScreen();
	WinScreen(const WinScreen&) = delete;
	WinScreen& operator=(const WinScreen&) = delete;
	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;

	Entity* m_screen = nullptr;
	Entity* m_background = nullptr;

};

