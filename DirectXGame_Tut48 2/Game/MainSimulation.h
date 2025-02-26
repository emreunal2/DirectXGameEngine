#pragma once
#include <DX3D/All.h>
#include <sstream>
#include "Scenario/Scenario.h"
#include "Scenario/FirstScenario.h"

class MainSimulation : public Game
{
public:
	MainSimulation();
	~MainSimulation();
	void onNewGame();
	void onLevelRestart();
	void onReturnToMainMenu();
	void ChangeScenario(Scenario newScenario);
protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
private:
	std::unique_ptr<Scenario> m_activeScenario = nullptr;
};

