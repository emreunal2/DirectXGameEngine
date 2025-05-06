#include "ScenarioMainMenu.h"
#include "../MainSimulation.h"

ScenarioMainMenu::ScenarioMainMenu(Game* game) : m_game(game)
{
}

ScenarioMainMenu::~ScenarioMainMenu()
{
	this->m_game->getWorld()->clear();
}

void ScenarioMainMenu::generateScenario()
{

}

void ScenarioMainMenu::onRestart()
{

}

void ScenarioMainMenu::onCreate()
{
	generateScenario();
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(7000.0f);
		m_camera->getTransform()->setPosition(Vector3D(60, 100, -50));
		m_camera->getTransform()->setRotation(Vector3D(0.307f, 0, 0));
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioMainMenu::onUpdate(f32 deltaTime)
{
	m_game->setTimeScale(0.4f);
	if (m_game->getInputSystem()->isKeyUp(Key::Enter))
	{
		static_cast<MainSimulation*>(m_game)->onMainMenu();
	}
}