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
	m_activeScenario = std::make_unique<Scenario>(this);
	m_activeScenario->onCreate();
}

void MainSimulation::onUpdate(f32 deltaTime)
{
	Game::onUpdate(deltaTime);
	m_activeScenario->onUpdate(deltaTime);
}

void MainSimulation::onNewGame()
{

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


