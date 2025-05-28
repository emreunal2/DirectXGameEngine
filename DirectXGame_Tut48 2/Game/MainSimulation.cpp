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

void MainSimulation::onGeneralDebugScenario()
{
	RestartScenarios();
	m_generalDebugScenario = std::make_unique<ScenarioGeneralDebug>(this);
	m_generalDebugScenario->onCreate();
	activeScenario = 5;
}
void MainSimulation::onAngularScenario()
{
	RestartScenarios();
	m_angularScenario = std::make_unique<ScenarioAngular>(this);
	m_angularScenario->onCreate();
	activeScenario = 6;
}

void MainSimulation::onElasticityScenario()
{
	RestartScenarios();
	m_elasticityScenario = std::make_unique<ScenarioElasticity>(this);
	m_elasticityScenario->onCreate();
	activeScenario = 7;
}
void MainSimulation::onMassScenario()
{
	RestartScenarios();
	m_massScenario = std::make_unique<ScenarioMass>(this);
	m_massScenario->onCreate();
	activeScenario = 8;
}
void MainSimulation::onUpdate(f32 deltaTime)
{
	Game::onUpdate(deltaTime);
	InputChecks();
	SceneUpdates(deltaTime);
	
	/**m_imguiManager->beginFrame();
	m_imguiManager->render();
	m_imguiManager->endFrame();
	*/
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
	if (m_mainMenu) m_mainMenu->onUpdate(deltaTime);
	else if (m_firstScenario) m_firstScenario->onUpdate(deltaTime);
	else if (m_secondScenario) m_secondScenario->onUpdate(deltaTime);
	else if (m_thirdScenario) m_thirdScenario->onUpdate(deltaTime);
	else if (m_fourthScenario) m_fourthScenario->onUpdate(deltaTime);
	else if (m_generalDebugScenario) m_generalDebugScenario->onUpdate(deltaTime);
	else if (m_angularScenario) m_angularScenario->onUpdate(deltaTime);
	else if (m_elasticityScenario) m_elasticityScenario->onUpdate(deltaTime);
	else if (m_activeScenario) m_activeScenario->onUpdate(deltaTime);
	else if (m_massScenario) m_massScenario->onUpdate(deltaTime);

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
	if (getInputSystem()->isKeyUp(Key::_5))
	{
		static_cast<MainSimulation*>(this)->onGeneralDebugScenario();
	}
	if (getInputSystem()->isKeyUp(Key::_6))
	{
		static_cast<MainSimulation*>(this)->onAngularScenario();
	}
	if (getInputSystem()->isKeyUp(Key::_7))
	{
		static_cast<MainSimulation*>(this)->onElasticityScenario();
	}
	if (getInputSystem()->isKeyUp(Key::_8))
	{
		static_cast<MainSimulation*>(this)->onMassScenario();
	}
}
void MainSimulation::RestartScenarios()
{
	this->pausePhysicsThread();
	if(m_mainMenu) m_mainMenu.reset();
	if(m_firstScenario) m_firstScenario.reset();
	if(m_secondScenario)m_secondScenario.reset();
	if(m_thirdScenario)m_thirdScenario.reset();
	if(m_fourthScenario)m_fourthScenario.reset();
	if(m_generalDebugScenario)m_generalDebugScenario.reset();
	if(m_angularScenario)m_angularScenario.reset();
	if(m_elasticityScenario)m_elasticityScenario.reset();
	if(m_massScenario)m_massScenario.reset();
	this->resumePhysicsThread();
}


