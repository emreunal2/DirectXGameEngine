#include "ScenarioGeneralDebug.h"
#include "../MainSimulation.h"
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"
#include "../Item/StaticCubeItem.h"

ScenarioGeneralDebug::ScenarioGeneralDebug(Game* game) : m_game(game)
{
}
ScenarioGeneralDebug::~ScenarioGeneralDebug()
{
	this->m_game->getWorld()->clear();
}

void ScenarioGeneralDebug::generateScenario()
{
	// Big Sphere A (light)
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		-4.0f, 0.0f, 0.0f,    // pos = left side
		6.0f, -2.0f, 0.0f,    // dir = right and slightly down
		4.0f,                 // mass = light
		MaterialType::DEFAULT
	);

	// Big Sphere B (heavy)
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		4.0f, 0.0f, 0.0f,     // pos = right side
		-3.0f, 1.0f, 0.0f,    // dir = left and slightly up
		1.0f,                 // mass = HEAVY
		MaterialType::DEFAULT
	);
}

void ScenarioGeneralDebug::onRestart()
{
}

void ScenarioGeneralDebug::onCreate()
{
	generateScenario();
	auto m_camera = m_game->getWorld()->createEntity<Entity>();
	auto cam = m_camera->createComponent<CameraComponent>();
	cam->setFarPlane(7000.0f);
	cam->setFieldOfView(1.3f);
	m_camera->getTransform()->setPosition(Vector3D(0, 15, -50));
	cam->setType(CameraType::Perspective);

	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioGeneralDebug::onUpdate(f32 deltaTime)
{
	if (m_game->getInputSystem()->isKeyUp(Key::Q))
	{
		auto type = MaterialType::DEFAULT;
		if (m_game->spawnerType == 0)
		{
			type = MaterialType::DEFAULT;
		}
		else if (m_game->spawnerType == 1)
		{
			type = MaterialType::GRASS;
		}
		else if (m_game->spawnerType == 2)
		{
			type = MaterialType::METAL;
		}
		else
		{
			type = MaterialType::DEFAULT;
		}
		CreateMovingSphere(m_game->spawnerRadius, m_game->spawnerX, m_game->spawnerY, m_game->spawnerZ,
			m_game->spawnerDirectionX, m_game->spawnerDirectionY, m_game->spawnerDirectionZ,
			m_game->spawnerMass, type);
	}
	if (m_game->getInputSystem()->isKeyUp(Key::E))
	{
		CreateStaticSphere(m_game->spawnerRadius, m_game->spawnerLenght, m_game->spawnerX, m_game->spawnerY, m_game->spawnerZ);
	}
	if (m_game->getInputSystem()->isKeyUp(Key::R))
	{
		CreateStaticCube(m_game->spawnerCubeSizeX, m_game->spawnerCubeSizeY, m_game->spawnerCubeSizeZ,
			m_game->spawnerX, m_game->spawnerY, m_game->spawnerZ);
	}
}

void ScenarioGeneralDebug::CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass, MaterialType type)
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

void ScenarioGeneralDebug::CreateStaticSphere(f32 radius, f32 lenght, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticSphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(radius, lenght, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
	entity->getComponent<SphereColliderComponent>()->setLength(lenght);
}

void ScenarioGeneralDebug::CreateStaticCube(f32 sizex, f32 sizey, f32 sizez, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticCubeItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(sizex, sizey, sizez));
	entity->getComponent<CubeColliderComponent>()->setExtents(Vector3D(sizex / 2, sizey / 2, sizez / 2));
}