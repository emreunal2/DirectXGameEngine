#include "ScenarioCube.h"
#include "../MainSimulation.h"
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"
#include "../Item/StaticCubeItem.h"

ScenarioCube::ScenarioCube(Game* game) : m_game(game)
{
}

ScenarioCube::~ScenarioCube()
{
	this->m_game->getWorld()->clear();
}

void ScenarioCube::generateScenario()
{
	// cube mide of the scene
	CreateStaticCube(10.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f);
	// spheres moves to the cube
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		-15.0f, 0.0f, 0.0f,    // pos = left side
		6.0f, 0, 0.0f,    // dir = right and slightly down
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	// same on right side
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		15.0f, 0.0f, 0.0f,     // pos = right side
		-6.0f, 0.0f, 0.0f,    // dir = left and slightly up
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	//same on top
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		0.0f, 15.0f, 0.0f,    // pos = top side
		0.0f, -6.0f, 0.0f,    // dir = down
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	//same on bottom
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		0.0f, -15.0f, 0.0f,    // pos = bottom side
		0.0f, 6.0f, 0.0f,    // dir = up
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	//same on front
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		0.0f, 0.0f, 15.0f,    // pos = front side
		0.0f, 0.0f, -6.0f,    // dir = back
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	//same on back
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		0.0f, 0.0f, -15.0f,    // pos = back side
		0.0f, 0.0f, 6.0f,    // dir = front
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	// from top left corner
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		-15.0f, 15.0f, -15.0f,    // pos = top left corner
		6.0f, -6.0f, 6.0f,    // dir = right and slightly down
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
	// from top right corner
	CreateMovingSphere(
		2.0f,                 // radius = BIG
		15.0f, 15.0f, -15.0f,     // pos = top right corner
		-6.0f, -6.0f, 6.0f,    // dir = left and slightly down
		1.0f,                 // mass = light
		MaterialType::DEFAULT
	);
}

void ScenarioCube::onRestart()
{
}

void ScenarioCube::onCreate()
{
	generateScenario();
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(500.0f);
		cam->setFieldOfView(1.5f);
		cam->setType(CameraType::Perspective);

		// Step back and look slightly further down
		m_camera->getTransform()->setPosition(Vector3D(0, 25, -30));
		m_camera->getTransform()->setRotation(Vector3D(0.5f, 0.0f, 0.0f));

		m_game->getInputSystem()->lockCursor(false);
	}
}

void ScenarioCube::onUpdate(f32 deltaTime)
{
	//get all objects
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

void ScenarioCube::CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass, MaterialType type)
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

void ScenarioCube::CreateStaticSphere(f32 radius, f32 lenght, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticSphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(radius, lenght, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
	entity->getComponent<SphereColliderComponent>()->setLength(lenght);
}

void ScenarioCube::CreateStaticCube(f32 sizex, f32 sizey, f32 sizez, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticCubeItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(sizex, sizey, sizez));
	entity->getComponent<CubeColliderComponent>()->setExtents(Vector3D(sizex / 2, sizey / 2, sizez / 2));
}