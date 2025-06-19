#include "MainMenu.h"
#include "../../MainGame.h"
#include <sstream>
#include "../../Item/BoxItem.h"
#include "../../Item/Platform.h"
MainMenu::MainMenu(Game* game) : m_game(game)
{
	auto font = game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");
	auto sphere = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto spaceship = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/house.obj");
	auto sky = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto normalMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/NormalMap.jpg");
	auto heightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto waveHeightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/waveHeightMap.png");
	auto grass = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");
	auto skyMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");
	auto mat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	auto gameMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
	auto ToonShading = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/ToonShading.hlsl");
	auto bumpShading = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Bump.hlsl");
	auto displacementShading = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Displacement.hlsl");


	/* {
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto m_terrainComponent = entity->createComponent<TerrainComponent>();
		m_terrainComponent->setHeightMap(heightMap);
		m_terrainComponent->setGroundMap(grass);
		m_terrainComponent->setCliffMap(ground);

		auto transform = entity->getTransform();
		transform->setScale(Vector3D(1, 1, 1));
	}*/
	//Base
	{
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto meshComponent = entity->createComponent<MeshComponent>();
		meshComponent->setMesh(spaceship);
		mat->addTexture(normalMap);
		meshComponent->addMaterial(mat);
		entity->getTransform()->setPosition(Vector3D(50, 75, 100));
		entity->getTransform()->setScale(Vector3D(25, 25, 25));
	}
	//Toon
	{
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto meshComponent = entity->createComponent<MeshComponent>();
		meshComponent->setMesh(spaceship);
		ToonShading->addTexture(normalMap);
		meshComponent->addMaterial(ToonShading);
		entity->getTransform()->setPosition(Vector3D(125, 75, 100));
		entity->getTransform()->setScale(Vector3D(25, 25, 25));
	}
	//Bump
	{
		auto entity1 = m_game->getWorld()->createEntity<Entity>();
		auto meshComponent1 = entity1->createComponent<MeshComponent>();
		meshComponent1->setMesh(spaceship);
		bumpShading->addTexture(normalMap);
		meshComponent1->addMaterial(bumpShading);
		entity1->getTransform()->setPosition(Vector3D(-25, 75, 100));
		entity1->getTransform()->setScale(Vector3D(25, 25, 25));
	}
	{
		auto entity1 = m_game->getWorld()->createEntity<Entity>();
		auto meshComponent1 = entity1->createComponent<MeshComponent>();
		meshComponent1->setMesh(spaceship);
		displacementShading->addTexture(normalMap);
		meshComponent1->addMaterial(displacementShading);
		entity1->getTransform()->setPosition(Vector3D(-100, 75, 100));
		entity1->getTransform()->setScale(Vector3D(25, 25, 25));
	}

	//sea
	{
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto waterComponent = entity->createComponent<WaterComponent>();
		waterComponent->setWaveHeightMap(waveHeightMap);

		auto transform = entity->getTransform();
		transform->setPosition(Vector3D(-768, 15, -768));
	}

	//fog
	{
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto fogComponent = entity->createComponent<FogComponent>();
		fogComponent->setData(Vector4D(0.4f, 0.5f, 0.7f, 1.0f), 50, 600);
	}

	//light
	{
		m_lightEntity = m_game->getWorld()->createEntity<Entity>();
		auto lightComponent = m_lightEntity->createComponent<LightComponent>();
		lightComponent->setColor(Vector4D(1.0f, 1.0f, 1.0f, 1));
		m_lightEntity->getTransform()->setRotation(Vector3D(0.0f, 0.0f, 0.0f)); // start from neutral
	}

	//camera
	{
		auto m_camera = m_game->getWorld()->createEntity<Entity>();
		auto cam = m_camera->createComponent<CameraComponent>();
		cam->setFarPlane(7000.0f);
		m_camera->getTransform()->setPosition(Vector3D(60, 100, -50));
		m_camera->getTransform()->setRotation(Vector3D(0.307f,0,0));
	}

	m_game->getInputSystem()->lockCursor(false);
	m_game->setTimeScale(1.0f);
}


MainMenu::~MainMenu()
{
	try {
		this->m_game->getWorld()->clear();
	}
	catch(...) {
		// Handle any exceptions that might occur during cleanup
	}
}

void MainMenu::onUpdate(f32 deltaTime)
{
	m_angle += 3.14f * deltaTime;
	//m_sphereEntity->getTransform()->setRotation(Vector3D(0, m_angle * 0.4f, 0));
	static float angle = 0.0f;
	angle += deltaTime * 0.5f; // slow rotation

	// Circle light direction in XZ plane
	float dirX = cos(angle);
	float dirZ = sin(angle);

	// Keep it diagonally downward to still affect vertical surfaces
	Vector3D lightDir = Vector3D(dirX, -1.0f, dirZ);

	m_lightEntity->getTransform()->setRotation(lightDir);
	if (m_game->getInputSystem()->isKeyUp(Key::Enter))
	{
		static_cast<MainGame*>(m_game)->onNewGame();
	}
}



