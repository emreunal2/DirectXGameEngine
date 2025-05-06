#include "MainSimulation.h"

MainSimulation::MainSimulation()
{
}

MainSimulation::~MainSimulation()
{
}

void MainSimulation::onCreate()
{
	//Creates the game and main menu
	Game::onCreate();
	m_mainMenu = std::make_unique<ScenarioMainMenu>(this);
	m_mainMenu->onCreate();
	activeScenario = 0;
}
void MainSimulation::onMainMenu()
{
	RestartScenarios();
	m_mainMenu = std::make_unique<ScenarioMainMenu>(this);
	m_mainMenu->onCreate();
}

void MainSimulation::onFirstScenario()
{
	RestartScenarios();
	m_firstScenario = std::make_unique<ScenarioFirst>(this);
	m_firstScenario->onCreate();
	activeScenario = 1;
}

void MainSimulation::onSecondScenario()
{
	RestartScenarios();
	m_secondScenario = std::make_unique<ScenarioSecond>(this);
	m_secondScenario->onCreate();
	activeScenario = 2;
}
void MainSimulation::onThirdScenario()
{
	RestartScenarios();
	m_thirdScenario = std::make_unique<ScenarioThird>(this);
	m_thirdScenario->onCreate();
	activeScenario = 3;
}
void MainSimulation::onFourthScenario()
{
	RestartScenarios();
	m_fourthScenario = std::make_unique<ScenarioFourth>(this);
	m_fourthScenario->onCreate();
	activeScenario = 4;
}
void MainSimulation::onUpdate(f32 deltaTime)
{
	Game::onUpdate(deltaTime);
	InputChecks();
	SceneUpdates(deltaTime);
}



void MainSimulation::onNewGame()
{
	m_activeScenario.reset();
	m_activeScenario = std::make_unique<Scenario>(this);
	m_activeScenario->onCreate();
}

void MainSimulation::onLevelRestart()
{

}

void MainSimulation::SceneUpdates(f32 deltaTime)
{
	if (m_activeScenario) m_activeScenario->onUpdate(deltaTime);
	if (m_mainMenu) m_mainMenu->onUpdate(deltaTime);
	if (m_firstScenario) m_firstScenario->onUpdate(deltaTime);
	if (m_secondScenario) m_secondScenario->onUpdate(deltaTime);
	if (m_thirdScenario) m_thirdScenario->onUpdate(deltaTime);
	if (m_fourthScenario) m_fourthScenario->onUpdate(deltaTime);
}

void MainSimulation::InputChecks()
{
	if (getInputSystem()->isKeyUp(Key::Escape))
	{
		static_cast<MainSimulation*>(this)->onMainMenu();
	}
	if (getInputSystem()->isKeyUp(Key::_1))
	{
		static_cast<MainSimulation*>(this)->onFirstScenario();
	}
	if (getInputSystem()->isKeyUp(Key::_2))
	{
		static_cast<MainSimulation*>(this)->onSecondScenario();
	}
	if (getInputSystem()->isKeyUp(Key::_3))
	{
		static_cast<MainSimulation*>(this)->onThirdScenario();
	}
	if (getInputSystem()->isKeyUp(Key::_4))
	{
		static_cast<MainSimulation*>(this)->onFourthScenario();
	}
}
void MainSimulation::RestartScenarios()
{
	m_mainMenu.reset();
	m_firstScenario.reset();
}
