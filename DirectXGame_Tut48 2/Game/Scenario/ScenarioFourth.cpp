#include "ScenarioFourth.h"
#include "../MainSimulation.h"

ScenarioFourth::ScenarioFourth(Game* game) : m_game(game)
{
}
ScenarioFourth::~ScenarioFourth()
{
	this->m_game->getWorld()->clear();
}

void ScenarioFourth::generateScenario()
{

}

void ScenarioFourth::onRestart()
{
}

void ScenarioFourth::onCreate()
{
	generateScenario();
	m_game->setTimeScale(0.4f);
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(7000.0f);
		m_camera->getTransform()->setPosition(Vector3D(60, 100, -50));
		m_camera->getTransform()->setRotation(Vector3D(0.307f, 0, 0));
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioFourth::onUpdate(f32 deltaTime)
{

}