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

#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Game/World.h>

#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Resource/Mesh.h>
#include <DX3D/Resource/Texture.h>
#include <DX3D/Resource/Material.h>

#include <DX3D/Input/InputSystem.h>

#include <DX3D/Physics/PhysicsEngine.h>

Game::Game()
{
	m_inputSystem = std::make_unique<InputSystem>();
	m_physicsEngine = std::make_unique<PhysicsEngine>(this);
	m_graphicsEngine = std::make_unique<GraphicsEngine>(this);
	m_display = std::make_unique<Display>(this);
	m_resourceManager = std::make_unique<ResourceManager>(this);
	m_world = std::make_unique<World>(this);

	m_inputSystem->setLockArea(m_display->getClientSize());
}

Game::~Game()
{
}

PhysicsEngine* Game::getPhysicsEngine()
{
	return m_physicsEngine.get();
}

GraphicsEngine* Game::getGraphicsEngine()
{
	return m_graphicsEngine.get();
}

World* Game::getWorld()
{
	return m_world.get();
}

InputSystem* Game::getInputSystem()
{
	return m_inputSystem.get();
}

ResourceManager* Game::getResourceManager()
{
	return m_resourceManager.get();
}

Display* Game::getDisplay()
{
	return m_display.get();
}

void Game::onDisplaySize(const Rect& size)
{
	m_inputSystem->setLockArea(m_display->getClientSize());
	onInternalUpdate();
}

void Game::onInternalUpdate()
{
	//computing delta time
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();
	if (m_previousTime.time_since_epoch().count())
		elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;

	auto deltaTime = (f32)elapsedSeconds.count();
	deltaTime *= m_timeScale;
	m_totalTime += deltaTime;

	m_inputSystem->update();


	onUpdate(deltaTime);
	m_world->update(deltaTime);


	m_physicsEngine->update();
	m_graphicsEngine->update();
}

void Game::quit()
{
	m_isRunning = false;
}