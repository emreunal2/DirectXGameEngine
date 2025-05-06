#pragma once
#include <DX3D/All.h>
#include <sstream>
#include "Scenario/Scenario.h"
#include "Scenario/FirstScenario.h"
#include "Scenario/ScenarioMainMenu.h"
#include "Scenario/ScenarioFirst.h"
#include "UI/MainMenu/MainMenu.h"
#include "Level/Level.h"

class MainSimulation : public Game
{
public:
	MainSimulation();
	~MainSimulation();
	void onNewGame();
	void onLevelRestart();
	void onMainMenu();
	void onFirstScenario();
	void RestartScenarios();
protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	void SceneUpdates(f32 deltaTime);
	void InputChecks();
private:
	std::unique_ptr<Scenario> m_activeScenario = nullptr;
	std::unique_ptr<ScenarioFirst> m_firstScenario = nullptr;
	std::unique_ptr<ScenarioMainMenu> m_mainMenu = nullptr;
	int activeScenario = NULL;

};

