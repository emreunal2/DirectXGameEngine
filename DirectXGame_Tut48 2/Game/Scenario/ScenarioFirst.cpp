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
	/*
	for (int i = 0; i < 15; i++)
	{
		float radius = static_cast<float>((std::rand() % 3) + 1);
		float length = radius + rand() % 2;
		float posX = static_cast<float>((std::rand() % 90) - 45);
		float posY = static_cast<float>((std::rand() % 20) - 10);
		float posZ = static_cast<float>((std::rand() % 90) - 45);
		CreateStaticSphere(radius, length, posX, posY, posZ);
	}

	// Add moving spheres one by one from random points above the scene
	for (int i = 0; i < 100; i++)
	{
		float startX = static_cast<float>((std::rand() % 90) - 45);
		float startY = static_cast<float>((std::rand() % 30) + 10);
		float startZ = static_cast<float>((std::rand() % 90) - 45);

		float dirX = static_cast<float>((std::rand() % 10) - 5);
		float dirY = static_cast<float>((std::rand() % 10) - 5);
		float dirZ = static_cast<float>((std::rand() % 10) - 5);

		CreateMovingSphere(1.5f, startX, startY, startZ, dirX, dirY, dirZ);
	}*/
	//CreateStaticSphere(3.0f,6.0f,0,0,0);
	//CreateMovingSphere(1.0f, 0, 15, 0, 0, -20, 0);
	//CreateMovingSphere(2.0f, 15, 0, 0, -15, 0, 0);
	//CreateMovingSphere(1.0f, -15, 15, 0, 15, -15, 0);

	CreateMovingSphere(2.0f, 15, 15, 15, -30, 0, 0,10, MaterialType::DEFAULT);
	CreateMovingSphere(1.0f, -15, 15, 15, 0, 0, 0,30, MaterialType::METAL);

	//CreateStaticCube(5.0f, -10, 15, 15);
	//CreateMovingSphere(1.0f, -10, 25, 15, 0, -5, 0);

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

		m_camera->getTransform()->setPosition(Vector3D(0, 15, -50));
		
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioFirst::onUpdate(f32 deltaTime)
{
	//get all objects

}

void ScenarioFirst::CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass, MaterialType type)
{
	auto entity = m_game->getWorld()->createEntity<SphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->setDirection(Vector3D(dirx, diry, dirz));
	entity->getTransform()->setScale(Vector3D(radius, radius, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
	entity->getComponent<SphereColliderComponent>()->setLength(radius);
	entity->setMass(mass);
	entity->setMaterialType(type);
}

void ScenarioFirst::CreateStaticSphere(f32 radius, f32 lenght, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticSphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(radius, lenght, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
	entity->getComponent<SphereColliderComponent>()->setLength(lenght);
}

void ScenarioFirst::CreateStaticCube(f32 size, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticCubeItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(size, size, size));
	entity->getComponent<SphereColliderComponent>()->setRadius(size/2);
}
