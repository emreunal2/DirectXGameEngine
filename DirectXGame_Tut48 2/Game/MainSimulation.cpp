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
}
void MainSimulation::RestartScenarios()
{
	m_mainMenu.reset();
	m_firstScenario.reset();
}
