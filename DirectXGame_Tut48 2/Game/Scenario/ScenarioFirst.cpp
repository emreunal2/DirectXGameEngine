#include "ScenarioFirst.h"
#include "../MainSimulation.h"
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"

ScenarioFirst::ScenarioFirst(Game* game) : m_game(game)
{
}

ScenarioFirst::~ScenarioFirst()
{
	this->m_game->getWorld()->clear();
}

void ScenarioFirst::generateScenario()
{
	//Create 25 spheres with random velocity and position
	/*
	for (int i = 0; i < 25; i++)
	{
		auto entity = m_game->getWorld()->createEntity<SphereItem>();
		entity->getTransform()->setPosition(Vector3D(rand() % 100, rand() % 100, rand() % 100));
		//entity->getTransform()->setRotation(Vector3D(rand() % 360, rand() % 360, rand() % 360));
		entity->setDirection(Vector3D(rand() % 10, rand() % 10, rand() % 10));


		entity->getTransform()->setScale(Vector3D(5, 5, 5));

	}
	*/
	auto entity = m_game->getWorld()->createEntity<SphereItem>();
	entity->getTransform()->setPosition(Vector3D(0, 70, 70));
	entity->setDirection(Vector3D(15, 0, 0));

	auto entity2 = m_game->getWorld()->createEntity<SphereItem>();
	entity2->getTransform()->setPosition(Vector3D(70, 70, 70));
	entity2->setDirection(Vector3D(-50, 0, 0));

	// Create a static sphere
	//auto entity = m_game->getWorld()->createEntity<StaticSphereItem>();
	//entity->getTransform()->setPosition(Vector3D(rand() % 100, rand() % 100, rand() % 100));
	//auto entity = m_game->getWorld()->createEntity<SphereItem>();
	//entity->getTransform()->setPosition(Vector3D(70, 70, 70));
}

void ScenarioFirst::onRestart()
{
}

void ScenarioFirst::onCreate()
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

void ScenarioFirst::onUpdate(f32 deltaTime)
{
	//get all objects

}

