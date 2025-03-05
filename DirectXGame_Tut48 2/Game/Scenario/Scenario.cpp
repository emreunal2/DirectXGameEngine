#include "Scenario.h"
#include "../MainSimulation.h"

Scenario::Scenario(Game* game) : m_game(game)
{
}

Scenario::~Scenario()
{
	this->m_game->getWorld()->clear();
}

void Scenario::generateScenario()
{
	auto sphere = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto sky = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto heightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto waveHeightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/waveHeightMap.png");
	auto grass = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");
	auto skyMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");
	auto mat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	
	{
		m_sphereEntity = m_game->getWorld()->createEntity<Entity>();
		auto meshComponent = m_sphereEntity->createComponent<MeshComponent>();
		meshComponent->setMesh(sphere);
		mat->addTexture(heightMap);
		meshComponent->addMaterial(mat);
		
		auto transform = m_sphereEntity->getTransform();
		transform->setScale(Vector3D(25, 25, 25));
		transform->setPosition(Vector3D(75, 75, 100));
	}
}

void Scenario::onRestart()
{

}

void Scenario::onCreate()
{
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(7000.0f);
		m_camera->getTransform()->setPosition(Vector3D(60, 100, -50));
		m_camera->getTransform()->setRotation(Vector3D(0.307f, 0, 0));
	}
	m_game->getInputSystem()->lockCursor(false);
	auto sphere = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto sky = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto heightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto waveHeightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/waveHeightMap.png");
	auto grass = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");
	auto skyMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");
	auto font = m_game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");

	auto logo = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/logo.png");
	auto cross = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/cross.png");
	auto health = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/health.png");
	auto ammo = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/ammo.png");

	skyMat->addTexture(sky);
	skyMat->setCullMode(CullMode::Front);

	generateScenario();
}

void Scenario::onUpdate(f32 deltaTime)
{
	m_angle += 3.14f * deltaTime;
	m_sphereEntity->getTransform()->setRotation(Vector3D(0, m_angle * 0.4f, 0));
}