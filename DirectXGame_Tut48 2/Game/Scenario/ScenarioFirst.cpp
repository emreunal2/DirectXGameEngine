#include "ScenarioFirst.h"
#include "../MainSimulation.h"
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"
#include "../Item/StaticCubeItem.h"

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

	{
		//cube creation
		//auto cubeBottom = m_game->getWorld()->createEntity<StaticCubeItem>();
		//cubeBottom->getTransform()->setPosition(Vector3D(0, -30, 0));
		//cubeBottom->getTransform()->setScale(Vector3D(90, 0, 90));
		//auto cubeTop = m_game->getWorld()->createEntity<StaticCubeItem>();
		//cubeTop->getTransform()->setPosition(Vector3D(0, 30, 0));
		//cubeTop->getTransform()->setScale(Vector3D(90, 0, 90));
		//auto cubeLeft = m_game->getWorld()->createEntity<StaticCubeItem>();
		//cubeLeft->getTransform()->setPosition(Vector3D(-30, 0, 0));
		//cubeLeft->getTransform()->setScale(Vector3D(1, 1, 15));
	}
	
	
	
	//auto entity = m_game->getWorld()->createEntity<SphereItem>();
	//entity->getTransform()->setPosition(Vector3D(0, 0, 0));
	//entity->setDirection(Vector3D(15, 0, 0));

	//auto entity2 = m_game->getWorld()->createEntity<StaticCubeItem>();
	//entity2->getTransform()->setPosition(Vector3D(0, 0, 0));
	//entity2->getTransform()->setScale(Vector3D(2, 2, 2));
	
	//auto entity3 = m_game->getWorld()->createEntity<StaticCubeItem>();
	//entity3->getTransform()->setPosition(Vector3D(2, 0, 0));
	//entity3->getTransform()->setScale(Vector3D(2, 2, 2));

	CreateMovingSphere(3.0f, -15, 0, 0, 15, 0, 0);
	CreateMovingSphere(3.0f, 15, 0, 0, -15, 0, 0);
	auto entity = m_game->getWorld()->createEntity<StaticCubeItem>();
	entity->getTransform()->setPosition(Vector3D(0, 0, 0));

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
		cam->setFieldOfView(1.3f);
		cam->setType(CameraType::Perspective);

		m_camera->getTransform()->setPosition(Vector3D(0, 0, -50));
		
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioFirst::onUpdate(f32 deltaTime)
{
	//get all objects

}

void ScenarioFirst::CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz)
{
	auto entity = m_game->getWorld()->createEntity<SphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->setDirection(Vector3D(dirx, diry, dirz));
	entity->getTransform()->setScale(Vector3D(radius, radius, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
}

void ScenarioFirst::CreateStaticSphere(f32 radius, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticSphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(radius, radius, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
}

