#include "ScenarioThird.h"
#include "../MainSimulation.h"

ScenarioThird::ScenarioThird(Game* game) : m_game(game)
{
}

ScenarioThird::~ScenarioThird()
{
	this->m_game->getWorld()->clear();
}

void ScenarioThird::generateScenario()
{

}

void ScenarioThird::onRestart()
{
}
void ScenarioThird::onCreate()
{
	generateScenario();
	m_game->setTimeScale(0.3f);
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(7000.0f);
		m_camera->getTransform()->setPosition(Vector3D(60, 100, -50));
		m_camera->getTransform()->setRotation(Vector3D(0.307f, 0, 0));
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioThird::onUpdate(f32 deltaTime)
{

}
