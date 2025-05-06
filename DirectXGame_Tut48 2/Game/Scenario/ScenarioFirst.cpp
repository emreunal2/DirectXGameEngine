#include "ScenarioFirst.h"
#include "../MainSimulation.h"

ScenarioFirst::ScenarioFirst(Game* game) : m_game(game)
{
}

ScenarioFirst::~ScenarioFirst()
{
	this->m_game->getWorld()->clear();
}

void ScenarioFirst::generateScenario()
{

}

void ScenarioFirst::onRestart()
{
}

void ScenarioFirst::onCreate()
{
	generateScenario();
	m_game->setTimeScale(0.1f);
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(7000.0f);
		m_camera->getTransform()->setPosition(Vector3D(60, 100, -50));
		m_camera->getTransform()->setRotation(Vector3D(0.307f, 0, 0));
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioFirst::onUpdate(f32 deltaTime)
{
	//m_game->setTimeScale(0.1f);
	//if (m_game->getInputSystem()->isKeyUp(Key::Escape))
	//{
		//static_cast<MainSimulation*>(m_game)->onMainMenu();
	//}
}