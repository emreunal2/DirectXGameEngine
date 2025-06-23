#include "Level.h"
#include "../MainGame.h"
#include "../Item/Spaceship.h"
#include "../Item/BoxItem.h"
#include "../Item/AsteroidItem.h"
#include <time.h>
#include "../Item/Platform.h"

Level::Level(Game* game) : m_game(game)
{
}

Level::~Level()
{
	try {
		m_winScreen.reset();
		m_gameOverScreen.reset();
		m_hud.reset();

		this->m_game->getWorld()->clear();
	}
	catch(...) {
		// Handle any exceptions that may occur during cleanup
	}
}

Entity* Level::getPlayer()
{
	return m_player;
}

void Level::toggleLightingMode()
{
	if (m_lightingMode == LightingMode::Daylight)
	{
		m_lightingMode = LightingMode::Torch;
	}
	else
	{
		m_lightingMode = LightingMode::Daylight;
	}
	updateLighting();
}

void Level::updateLighting()
{
	if (m_lightingMode == LightingMode::Daylight)
	{
		m_directionalLight->setColor(Vector4D(255.0f, 1.0f, 1.0f, 1));
		m_spotLight->setColor(Vector4D(0, 0, 0, 0)); // Disable spot light
	}
	else
	{
		m_directionalLight->setColor(Vector4D(0, 0, 0, 0)); // Disable directional light
		m_spotLight->setColor(Vector4D(255.0f, 1.0f, 1.0f, 1));
	}
}

void Level::generateLevel()
{
	auto sphere = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto heightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto waveHeightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/waveHeightMap.png");
	auto grass = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");
	auto house = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/house.obj");
	auto mat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");

	m_hud = std::make_unique<HUD>(this->m_game);

	//terrain
	{
		auto entity = m_game->getWorld()->createEntity<Entity>();
		m_terrainComponent = entity->createComponent<TerrainComponent>();
		m_terrainComponent->setHeightMap(heightMap);
		m_terrainComponent->setGroundMap(grass);
		m_terrainComponent->setCliffMap(ground);

		auto transform = entity->getTransform();
		transform->setScale(Vector3D(1, 1, 1));
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
		m_entity = m_game->getWorld()->createEntity<Entity>();
		m_entity->getTransform()->setRotation(Vector3D(-0.707f, 0.707f, 0));
		m_directionalLight = m_entity->createComponent<LightComponent>();
		m_directionalLight->setColor(Vector4D(1.0f, 1.0f, 1.0f, 1));
		m_entity->getTransform()->setRotation(Vector3D(-0.707f, 0.707f, 0));

		m_spotLight = m_game->getWorld()->createEntity<Entity>()->createComponent<LightComponent>();
		m_spotLight->setColor(Vector4D(255, 0.1f, 0.1f, 0.1f)); 
		
	}

	m_player = m_game->getWorld()->createEntity<Spaceship>();

	
	//create 10 sphere
	{
		mat->addTexture(ground);
		for (unsigned int i = 0; i < 20; i++)
		{
			auto entity = m_game->getWorld()->createEntity<Entity>();
			auto meshComponent = entity->createComponent<MeshComponent>();
			meshComponent->setMesh(house);
			meshComponent->addMaterial(mat);
			entity->getTransform()->setPosition(Vector3D(rand() % 100 + (-50.0f), (i * (20.0f)) - 5.0f, -100));
			entity->getTransform()->setScale(Vector3D(5, 5, 5));

		}
	}

	m_elapsedSecondsMatch = (f32)1;
	m_maximumScore = floor(((rand() % 50 + (10 * m_levels)) + 20 + (10 * m_levels)) / 10.0f);

	{
		for (unsigned int i = 0; i < 10; i++)
		{
			auto entity = m_game->getWorld()->createEntity<Platform>();
			entity->getTransform()->setPosition(Vector3D(rand()%100+(-50.0f), (i * (50.0f))-5.0f, 0));
			entity->getTransform()->setScale(Vector3D(rand()%60+50, 1, 1));

			auto boxEntity = m_game->getWorld()->createEntity<BoxItem>();
			auto pos = Vector3D((f32)(rand() % 100) + (-50.0f), (i * (50.0f)), 0);
			boxEntity->setPosition(pos);
		}
	}
}

void Level::onRestart()
{
	m_elapsedSecondsEnd = 0;
	m_sceneType = 2;
}

void Level::onCreate()
{
	srand((ui32)time(nullptr));

	FontUtility fontUtility;
	fontUtility.createFont(L"Bahnschrift", 32, L"Assets\\Fonts\\");


	auto sky = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto skyMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");
	auto font = m_game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift3.font");

	auto logo = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/logo.png");
	auto cross = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/cross.png");
	auto health = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/health.png");
	auto ammo = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/ammo.png");

	skyMat->addTexture(sky);
	skyMat->setCullMode(CullMode::Front);

	generateLevel();
	updateLighting();
}

void Level::onUpdate(f32 deltaTime)
{
	if (m_elapsedSecondsMatch <= 0 && m_sceneType == 0) {
		m_elapsedSecondsEnd = 5;
		m_elapsedSecondsMatch = 0;
		m_sceneType = 1;
		m_game->setTimeScale(0.0f);

		auto* spaceship = dynamic_cast<Spaceship*>(m_player);
		if (spaceship && static_cast<i32>(spaceship->getScore()) >= static_cast<i32>(m_maximumScore))
		{
			m_levels++;
			m_totalScore += spaceship->getScore();
			m_winScreen = std::make_unique<WinScreen>(this->m_game);
		}
		else
		{
			m_levels = 1;
			m_totalScore = 0;
			m_gameOverScreen = std::make_unique<GameOverScreen>(this->m_game);
		}
	}
	if (m_elapsedSecondsEnd <= 0 && m_sceneType == 1)
	{
		m_elapsedSecondsEnd = 0;
		m_sceneType = 2;
	}

	if (m_sceneType == 1)
	{
		m_elapsedSecondsEnd -= deltaTime;
	}
	else if (m_sceneType == 2)
	{
		m_sceneType = 0;
		m_elapsedSecondsEnd = 0;

		m_winScreen.reset();
		m_gameOverScreen.reset();
		m_hud.reset();

		this->m_game->getWorld()->clear();

		generateLevel();

		m_game->setTimeScale(1.0f);
	}

	m_elapsedSecondsMatch += deltaTime;
	m_rotation += 1.57f * deltaTime;

	m_entity->getTransform()->setRotation(Vector3D(0.707f, -3.14f, 0));
	auto clientSize = m_game->getDisplay()->getClientSize();

	if (m_sceneType == 1)
	{
		if (auto* spaceship = dynamic_cast<Spaceship*>(m_player))
		{
			if ((i32)spaceship->getScore() >= (i32)m_maximumScore)
			{
				m_winScreen->onUpdate(deltaTime);
			}
		}
		else
		{
			m_gameOverScreen->onUpdate(deltaTime);
		}
	}
	else if (m_sceneType == 0)
	{
		if (auto* spaceship = dynamic_cast<Spaceship*>(m_player))
		{
			m_hud->setInfo(m_levels, (i32)spaceship->getScore(), (i32)m_totalScore, (i32)m_elapsedSecondsMatch);
		}
	}

	m_hud->onUpdate(deltaTime);

	if (m_game->getInputSystem()->isKeyUp(Key::Escape))
	{
		if (auto* game = dynamic_cast<MainGame*>(m_game))
		{
			game->onReturnToMainMenu();
		}

	}
	if (m_game->getInputSystem()->isKeyUp(Key::R))
	{
		onRestart();
	}
	if (m_game->getInputSystem()->isKeyUp(Key::T))
	{
		toggleLightingMode();
	}

	if (m_lightingMode == LightingMode::Torch)
	{
		auto playerTransform = m_player->getTransform();
		m_spotLight->getEntity()->getTransform()->setPosition(playerTransform->getPosition());
		m_spotLight->getEntity()->getTransform()->setRotation(playerTransform->getRotation());
	}

	m_elapsedSecondsAsteroids += deltaTime;
	m_elapsedSecondsScores += deltaTime;

	if (m_elapsedSecondsScores > (1.0f + (0.125f * (f32)m_levels)))
	{
		//points
		m_elapsedSecondsScores = 0.0f;
		{
			//auto entity = m_game->getWorld()->createEntity<BoxItem>();
			//auto pos = Vector3D((f32)(rand() % 400) + (0.0f), (f32)(rand() % 100), 0);
			//entity->setPosition(pos);	
		}
	}


	if (m_elapsedSecondsAsteroids > (0.8f - (0.08f * (f32)m_levels)))
	{
		m_elapsedSecondsAsteroids = 0.0f;
		//asteroids
		{

			auto dirr = m_player->getTransform()->getPosition() + m_player->getTransform()->getDirection() * (400.0f - (25.0f * (f32)m_levels));

			auto entity = m_game->getWorld()->createEntity<AsteroidItem>();
			auto pos = Vector3D((f32)(dirr.x) + (f32)((rand() % 600) - 300),
				(f32)(rand() % 100) + (400.0f - (5.0f * (f32)m_levels)),
				(f32)(dirr.z) + (f32)((rand() % 600) - 300));
			auto dir = Vector3D::normalize(m_player->getTransform()->getPosition() - pos);

			entity->setAPosition(pos);
			entity->setADirection(dir);
		}
	}
}



