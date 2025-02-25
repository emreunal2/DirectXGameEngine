/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "MainMenu.h"
#include "../../MainGame.h"
#include <sstream>

MainMenu::MainMenu(Game* game) : m_game(game)
{
	auto font = game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");

	auto screen = game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/cpp3dgame_logo.png");
	auto pardcodeLogo = game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/pardcode_logo.png");
	auto background = game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/menu_background.png");

	{
		m_background = game->getWorld()->createEntity<Entity>();
		auto image = m_background->createComponent<ImageComponent>();
		image->setImage(background);
		image->setSize({ 0,0,0,0 });
		m_background->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_screen = game->getWorld()->createEntity<Entity>();
		auto image = m_screen->createComponent<ImageComponent>();
		image->setImage(screen);
		image->setSize({ 0,0,625,492 });
		m_screen->getTransform()->setPosition(Vector3D(10, 10, 0));
	}

	{
		m_pardcodeLogo = game->getWorld()->createEntity<Entity>();
		auto image = m_pardcodeLogo->createComponent<ImageComponent>();
		image->setImage(pardcodeLogo);
		image->setSize({ 0,0,437,137 });
		m_pardcodeLogo->getTransform()->setPosition(Vector3D(10, 10, 0));
	}

	auto sphere = m_game->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto sky = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto heightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto waveHeightMap = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/waveHeightMap.png");
	auto grass = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");
	auto skyMat = m_game->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");


	//terrain
	{
		auto entity = m_game->getWorld()->createEntity<Entity>();
		auto m_terrainComponent = entity->createComponent<TerrainComponent>();
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

	{
		m_optionSelector = m_game->getWorld()->createEntity<Entity>();
		auto text = m_optionSelector->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L">");
		m_optionSelector->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_options[0] = m_game->getWorld()->createEntity<Entity>();
		auto text = m_options[0]->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"New Game");
		m_options[0]->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_options[1] = m_game->getWorld()->createEntity<Entity>();
		auto text = m_options[1]->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"Quit");
		m_options[1]->getTransform()->setPosition(Vector3D(0, 0, 0));
	}


	m_game->getInputSystem()->lockCursor(true);
	m_game->setTimeScale(1.0f);
}


MainMenu::~MainMenu()
{
	this->m_game->getWorld()->clear();
}

void MainMenu::onUpdate(f32 deltaTime)
{
	auto clientSize = m_game->getDisplay()->getClientSize();


	auto image = m_background->getComponent<ImageComponent>();
	image->setSize({ 0,0,clientSize.width,clientSize.height });

	m_screen->getTransform()->setPosition(Vector3D(
		0,
		(f32)(clientSize.height / 2.0f) - 352.0f,
		0
	));

	m_pardcodeLogo->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.width) - 450.0f,
		0,
		0
	));

	for (ui32 i = 0; i < 2; i++)
	{
		m_options[i]->getTransform()->setPosition(Vector3D(
			70,
			((f32)(clientSize.height / 2.0f) - 352.0f)+ 492.0f + 20.0f +i*70.0f,
			0
		));
	}

	auto pos = m_options[m_selectedOption]->getTransform()->getPosition();

	m_optionSelector->getTransform()->setPosition({
		30,
		pos.y,
		0
	});


	if (m_game->getInputSystem()->isKeyUp(Key::ArrowDown))
	{
		m_selectedOption++;
		m_selectedOption %= 2;
	}
	if (m_game->getInputSystem()->isKeyUp(Key::ArrowUp))
	{
		m_selectedOption--;
		m_selectedOption %= 2;
	}

	if (m_game->getInputSystem()->isKeyUp(Key::Enter))
	{
		if (m_selectedOption == 0)
		{
			static_cast<MainGame*>(m_game)->onNewGame();
		}
		else if (m_selectedOption == 1)
		{
			static_cast<MainGame*>(m_game)->quit();
		}
	}
}



