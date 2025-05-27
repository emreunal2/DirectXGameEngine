#include "ScenarioMass.h"
#include "../MainSimulation.h"
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"
#include "../Item/StaticCubeItem.h"

ScenarioMass::ScenarioMass(Game* game)
	: m_game(game)
{
}
ScenarioMass::~ScenarioMass()
{
}

void ScenarioMass::generateScenario()
{

}

void ScenarioMass::onRestart()
{
}

void ScenarioMass::onCreate()
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

void ScenarioMass::onUpdate(f32 deltaTime)
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

}

void ScenarioMass::CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass, MaterialType type)
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