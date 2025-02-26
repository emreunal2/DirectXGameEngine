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
}

void Scenario::onRestart()
{

}

void Scenario::onCreate()
{
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

}