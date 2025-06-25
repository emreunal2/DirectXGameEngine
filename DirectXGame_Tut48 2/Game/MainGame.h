

#pragma once
#include <DX3D/All.h>
#include "Level/Level.h"
#include "UI/MainMenu/MainMenu.h"
#include <sstream>

class MainGame: public Game
{
public:
	MainGame();
	~MainGame();

	void onNewGame();
	void onLevelRestart();
	void onReturnToMainMenu();

protected:
	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;

private:
	std::unique_ptr<MainMenu> m_menu = nullptr;
	std::unique_ptr<Level> m_level = nullptr;
};

