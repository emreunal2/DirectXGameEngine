#include "MainSimulation.h"

MainSimulation::MainSimulation()
{
}

MainSimulation::~MainSimulation()
{
}

void MainSimulation::onCreate()
{
	Game::onCreate();
	//m_activeScenario = std::make_unique<Scenario>(this);
	//m_activeScenario->onCreate();

	m_mainMenu = std::make_unique<ScenarioMainMenu>(this);
	m_mainMenu->onCreate();
}
void MainSimulation::onMainMenu()
{
	m_activeScenario.reset();
	m_firstScenario.reset();
	m_mainMenu.reset();
	m_firstScenario = std::make_unique<Level>(this);
	m_firstScenario->onCreate();
}
void MainSimulation::onUpdate(f32 deltaTime)
{
	Game::onUpdate(deltaTime);
	if(m_activeScenario) m_activeScenario->onUpdate(deltaTime);
	if (m_mainMenu) m_mainMenu->onUpdate(deltaTime);
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

void MainSimulation::onReturnToMainMenu()
{

}

void MainSimulation::ChangeScenario(Scenario newScenario)
{

}


