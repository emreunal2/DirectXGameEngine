#pragma once
#include <DX3D/All.h>
#include <sstream>
#include "Scenario/Scenario.h"
#include "Scenario/FirstScenario.h"
#include "Scenario/ScenarioMainMenu.h"
#include "Scenario/ScenarioFirst.h"
#include "Scenario/ScenarioSecond.h"
#include "Scenario/ScenarioThird.h"
#include "Scenario/ScenarioFourth.h"
#include "Scenario/ScenarioGeneralDebug.h"
#include "UI/MainMenu/MainMenu.h"
#include "Level/Level.h"
#include "UI/ImGUIManager.h"

class MainSimulation : public Game
{
public:
	MainSimulation();
	~MainSimulation();
	void onNewGame();
	void onLevelRestart();
	void onMainMenu();
	void onFirstScenario();
	void onSecondScenario();
	void onThirdScenario();
	void onFourthScenario();
	void onGeneralDebugScenario();
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
	std::unique_ptr<ScenarioSecond> m_secondScenario = nullptr;
	std::unique_ptr<ScenarioThird> m_thirdScenario = nullptr;
	std::unique_ptr<ScenarioFourth> m_fourthScenario = nullptr;
	std::unique_ptr<ScenarioGeneralDebug> m_generalDebugScenario = nullptr;
	std::unique_ptr<ImGUIManager> m_imguiManager = nullptr;
	int activeScenario = NULL;

};

