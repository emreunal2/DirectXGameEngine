#include "ScenarioThird.h"
#include "../MainSimulation.h"
#include "../Item/SphereItem.h"
#include "../Item/StaticSphereItem.h"
#include "../Item/StaticCubeItem.h"

ScenarioThird::ScenarioThird(Game* game) : m_game(game)
{
}

ScenarioThird::~ScenarioThird()
{
	this->m_game->getWorld()->clear();
}

void ScenarioThird::generateScenario()
{
	// 3. Add many balls from random points in a scene with no fixed objects (apart from the surrounding cube). Moving spheres should be of different radii.
	for (int i = 0; i < 1000; ++i)
	{
		float radius = static_cast<float>((std::rand() % 2) + 1);
		float posX = static_cast<float>((std::rand() % 120) - 60);
		float posY = static_cast<float>((std::rand() % 120) - 60); // spawn from higher up
		float posZ = static_cast<float>((std::rand() % 120) - 60);
		float dirX = static_cast<float>((std::rand() % 10) - 5);
		float dirY = static_cast<float>((std::rand() % 10) - 5); // mostly downward
		float dirZ = static_cast<float>((std::rand() % 10) - 5);
		float mass = static_cast<float>((std::rand() % 10) + 1);

		CreateMovingSphere(radius, posX, posY, posZ, dirX, dirY, dirZ, mass, MaterialType::DEFAULT);
	}
}

void ScenarioThird::onRestart()
{
}
void ScenarioThird::onCreate()
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

		//floor
		auto floor = m_game->getWorld()->createEntity<StaticCubeItem>();
		floor->getTransform()->setPosition(Vector3D(0, -45.0f, 0));
		floor->getTransform()->setScale(Vector3D(90.0f, 10.0f, 90.0f));
		floor->getComponent<CubeColliderComponent>()->setExtents(Vector3D(90.0f / 2, 10.0f / 2, 90.0f / 2));
		floor->getComponent<MeshComponent>()->removeMaterial(0);
		auto tex = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/BaseRoom.hlsl");
		mat->addTexture(tex);
		floor->getComponent<MeshComponent>()->addMaterial(mat);
		//Ceiling
		auto ceiling = m_game->getWorld()->createEntity<StaticCubeItem>();
		ceiling->getTransform()->setPosition(Vector3D(0, 45.0f, 0));
		ceiling->getTransform()->setScale(Vector3D(90.0f, 10.0f, 90.0f));
		ceiling->getComponent<CubeColliderComponent>()->setExtents(Vector3D(90.0f / 2, 10.0f / 2, 90.0f / 2));
		ceiling->getComponent<MeshComponent>()->removeMaterial(0);
		auto tex2 = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat2 = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/BaseRoom.hlsl");
		mat2->addTexture(tex2);
		ceiling->getComponent<MeshComponent>()->addMaterial(mat2);
		// Left Wall
		auto leftWall = m_game->getWorld()->createEntity<StaticCubeItem>();
		leftWall->getTransform()->setPosition(Vector3D(-45.0f, 0, 0));
		leftWall->getTransform()->setScale(Vector3D(10.0f, 90.0f, 90.0f));
		leftWall->getComponent<CubeColliderComponent>()->setExtents(Vector3D(10.0f / 2, 90.0f / 2, 90.0f / 2));
		leftWall->getComponent<MeshComponent>()->removeMaterial(0);
		auto tex3 = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat3 = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/BaseRoom.hlsl");
		mat3->addTexture(tex3);
		leftWall->getComponent<MeshComponent>()->addMaterial(mat3);
		// Right Wall
		auto rightWall = m_game->getWorld()->createEntity<StaticCubeItem>();
		rightWall->getTransform()->setPosition(Vector3D(45.0f, 0, 0));
		rightWall->getTransform()->setScale(Vector3D(10.0f, 90.0f, 90.0f));
		rightWall->getComponent<CubeColliderComponent>()->setExtents(Vector3D(10.0f / 2, 90.0f / 2, 90.0f / 2));
		rightWall->getComponent<MeshComponent>()->removeMaterial(0);
		auto tex4 = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat4 = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/BaseRoom.hlsl");
		mat4->addTexture(tex4);
		rightWall->getComponent<MeshComponent>()->addMaterial(mat4);
		//back wall
		auto backWall = m_game->getWorld()->createEntity<StaticCubeItem>();
		backWall->getTransform()->setPosition(Vector3D(0, 0, -45.0f));
		backWall->getTransform()->setScale(Vector3D(90.0f, 90.0f, 10.0f));
		backWall->getComponent<CubeColliderComponent>()->setExtents(Vector3D(90.0f / 2, 90.0f / 2, 10.0f / 2));
		backWall->getComponent<MeshComponent>()->removeMaterial(0);
		auto tex5 = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat5 = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/BaseRoom.hlsl");
		mat5->addTexture(tex5);
		backWall->getComponent<MeshComponent>()->addMaterial(mat5);
		//front wall
		auto frontWall = m_game->getWorld()->createEntity<StaticCubeItem>();
		frontWall->getTransform()->setPosition(Vector3D(0, 0, 45.0f));
		frontWall->getTransform()->setScale(Vector3D(90.0f, 90.0f, 10.0f));
		frontWall->getComponent<CubeColliderComponent>()->setExtents(Vector3D(90.0f / 2, 90.0f / 2, 10.0f / 2));
		frontWall->getComponent<MeshComponent>()->removeMaterial(0);
		auto tex6 = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat6 = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/BaseRoom.hlsl");
		mat6->addTexture(tex6);
		frontWall->getComponent<MeshComponent>()->addMaterial(mat6);
	}
	m_game->getInputSystem()->lockCursor(false);
}

void ScenarioThird::onUpdate(f32 deltaTime)
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

void ScenarioThird::CreateMovingSphere(f32 radius, f32 posx, f32 posy, f32 posz, f32 dirx, f32 diry, f32 dirz, f32 mass, MaterialType type)
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

void ScenarioThird::CreateStaticSphere(f32 radius, f32 lenght, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticSphereItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(radius, lenght, radius));
	entity->getComponent<SphereColliderComponent>()->setRadius(radius);
	entity->getComponent<SphereColliderComponent>()->setLength(lenght);
}

void ScenarioThird::CreateStaticCube(f32 sizex, f32 sizey, f32 sizez, f32 posx, f32 posy, f32 posz)
{
	auto entity = m_game->getWorld()->createEntity<StaticCubeItem>();
	entity->getTransform()->setPosition(Vector3D(posx, posy, posz));
	entity->getTransform()->setScale(Vector3D(sizex, sizey, sizez));
	entity->getComponent<CubeColliderComponent>()->setExtents(Vector3D(sizex / 2, sizey / 2, sizez / 2));
}

