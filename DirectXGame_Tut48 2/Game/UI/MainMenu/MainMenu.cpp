#include "MainMenu.h"
#include "../../MainGame.h"
#include <sstream>
#include "../../Item/BoxItem.h"
#include "../../Item/Platform.h"
MainMenu::MainMenu(Game* game) : m_game(game)
{
	auto font = game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");
	auto sphere = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto sky = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto heightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto waveHeightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/waveHeightMap.png");
	auto grass = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");
	auto skyMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");
	auto mat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	auto gameMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
	auto ToonShading = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/ToonShading.hlsl");


	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"R: Restart game, ESC: Exit game");
		m_description->getTransform()->setPosition(Vector3D(250, 0, 0));
	}

	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"W/A/S/D: Movement, LookUp Direction");
		m_description->getTransform()->setPosition(Vector3D(250, 50, 0));
	}
	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"Space: Jump");
		m_description->getTransform()->setPosition(Vector3D(250, 100, 0));
	}
	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"-, =: Camera Zoom");
		m_description->getTransform()->setPosition(Vector3D(250, 150, 0));
	}
	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"<,>: Time Scale");
		m_description->getTransform()->setPosition(Vector3D(250, 200, 0));
	}

	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"T: Change Lighting");
		m_description->getTransform()->setPosition(Vector3D(250, 250, 0));
	}

	{
		m_description = m_game->getWorld()->createEntity<Entity>();
		auto text = m_description->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"Enter: Start the Game!!");
		m_description->getTransform()->setPosition(Vector3D(250, 500, 0));
	}

	/* {
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto m_terrainComponent = entity->createComponent<TerrainComponent>();
		m_terrainComponent->setHeightMap(heightMap);
		m_terrainComponent->setGroundMap(grass);
		m_terrainComponent->setCliffMap(ground);

		auto transform = entity->getTransform();
		transform->setScale(Vector3D(1, 1, 1));
	}*/

	{
		m_sphereEntity = m_game->getWorld()->createEntity<Platform>();
		auto meshComponent = m_sphereEntity->createComponent<MeshComponent>();
		auto transform = m_sphereEntity->getTransform();
		transform->setScale(Vector3D(25, 25, 25));
		transform->setPosition(Vector3D(75, 75, 100));
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
		auto m_entity = m_game->getWorld()->createEntity<Entity>();
		auto lightComponent = m_entity->createComponent<LightComponent>();
		lightComponent->setColor(Vector4D(1.0f, 1.0f, 1.0f, 1));
		m_entity->getTransform()->setRotation(Vector3D(0.707f, -3.14f, 0));
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
	this->m_game->getWorld()->clear();
}

void MainMenu::onUpdate(f32 deltaTime)
{
	m_angle += 3.14f * deltaTime;
	m_sphereEntity->getTransform()->setRotation(Vector3D(0, m_angle * 0.4f, 0));
	if (m_game->getInputSystem()->isKeyUp(Key::Enter))
	{
		static_cast<MainGame*>(m_game)->onNewGame();
	}
}



