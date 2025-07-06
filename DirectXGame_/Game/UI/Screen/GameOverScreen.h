

#pragma once
#include <DX3D/All.h>
#include <sstream>

class GameOverScreen
{
public:
	explicit GameOverScreen(Game* game);
	~GameOverScreen();
	GameOverScreen(const GameOverScreen&) = delete;
	GameOverScreen& operator=(const GameOverScreen&) = delete;
	void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;

	Entity* m_screen = nullptr;
	Entity* m_background = nullptr;

};

