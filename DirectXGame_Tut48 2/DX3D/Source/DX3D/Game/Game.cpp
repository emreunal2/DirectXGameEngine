

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
#include <Windows.h>
#include <chrono>
#include <thread>



Game::Game()
{
	m_inputSystem = std::make_unique<InputSystem>();
	m_physicsEngine = std::make_unique<PhysicsEngine>(this);
	m_graphicsEngine = std::make_unique<GraphicsEngine>(this);
	m_display = std::make_unique<Display>(this);
	m_resourceManager = std::make_unique<ResourceManager>(this);
	m_world = std::make_unique<World>(this);

	m_inputSystem->setLockArea(m_display->getClientSize());

	m_graphicsThread = std::thread(&Game::runGraphicsThread, this);
	std::cout << "Graphics thread started: "<< m_graphicsThread.get_id() << std::endl;
	m_physicsThread = std::thread(&Game::runPhysicsThread, this);
	std::cout << "Physics thread started: " << m_physicsThread.get_id() << std::endl;
	m_networkingThread = std::thread(&Game::runNetworkingThread, this);
	std::cout << "Networking thread started: " << m_networkingThread.get_id() << std::endl;
}

Game::~Game()
{
	m_isRunning = false;
	m_threadRunning = false;

	if (m_graphicsThread.joinable())
		m_graphicsThread.join();
	if (m_physicsThread.joinable())
		m_physicsThread.join();
	if (m_networkingThread.joinable())
		m_networkingThread.join();

	onQuit();
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

void Game::runGraphicsThread()
{
	SetThreadAffinityMask(GetCurrentThread(), GRAPHICS_CORE_MASK);
	std::cout << "Graphics thread Core: " << GetCurrentProcessorNumber() << std::endl;
	while (m_threadRunning)
	{
		std::cout << "Graphics thread Core: " << GetCurrentProcessorNumber() << std::endl;
		{
			std::lock_guard<std::mutex> lock(m_dataMutex);
			auto currentTime = std::chrono::system_clock::now();
			auto elapsedSeconds = std::chrono::duration<double>();
			if (m_previousTime.time_since_epoch().count())
				elapsedSeconds = currentTime - m_previousTime;
			m_previousTime = currentTime;

			auto deltaTime = (f32)elapsedSeconds.count();
			deltaTime *= m_timeScale;
			m_totalTime += deltaTime;

			//m_inputSystem->update();


			onUpdate(deltaTime);
			m_world->update(deltaTime);
			m_inputSystem->update();
			m_graphicsEngine->update();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		
	}
}

void Game::runPhysicsThread()
{
	SetThreadAffinityMask(GetCurrentThread(), PHYSICS_CORE_MASK);
	while (m_threadRunning)
	{

		{
			std::lock_guard<std::mutex> lock(m_dataMutex);

			m_physicsEngine->update();
			//m_graphicsEngine->update();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Game::runNetworkingThread()
{
	SetThreadAffinityMask(GetCurrentThread(), NETWORKING_CORE_MASK);
	while (m_threadRunning)
	{
		{
			std::lock_guard<std::mutex> lock(m_dataMutex);
			// Networking code would go here
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Game::onInternalUpdate()
{
	//computing delta time
	//auto currentTime = std::chrono::system_clock::now();
	//auto elapsedSeconds = std::chrono::duration<double>();
	//if (m_previousTime.time_since_epoch().count())
		//elapsedSeconds = currentTime - m_previousTime;
	//m_previousTime = currentTime;

	//auto deltaTime = (f32)elapsedSeconds.count();
	//deltaTime *= m_timeScale;
	//m_totalTime += deltaTime;

	//m_inputSystem->update();


	//onUpdate(deltaTime);
	//m_world->update(deltaTime);


	//m_physicsEngine->update();
	//m_graphicsEngine->update();
}

void Game::quit()
{
	m_isRunning = false;
	m_threadRunning = false;
}