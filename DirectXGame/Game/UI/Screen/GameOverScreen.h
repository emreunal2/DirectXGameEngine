

#pragma once
#include <DX3D/All.h>
#include <sstream>

class GameOverScreen
{
public:
	GameOverScreen(Game* game);
	~GameOverScreen();

	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;

	Entity* m_screen = nullptr;
	Entity* m_background = nullptr;

};

