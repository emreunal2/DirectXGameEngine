

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
#include <atomic>



Game::Game()
{
	m_inputSystem = std::make_unique<InputSystem>();
	m_physicsEngine = std::make_unique<PhysicsEngine>(this);
	m_graphicsEngine = std::make_unique<GraphicsEngine>(this);
	m_display = std::make_unique<Display>(this);
	m_resourceManager = std::make_unique<ResourceManager>(this);
	m_world = std::make_unique<World>(this);

	m_inputSystem->setLockArea(m_display->getClientSize());

	//m_graphicsThread = std::thread(&Game::runGraphicsThread, this);
	//std::cout << "Graphics thread started: "<< m_graphicsThread.get_id() << std::endl;
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
/*
void Game::runGraphicsThread()
{
	SetThreadAffinityMask(GetCurrentThread(), GRAPHICS_CORE_MASK);
	std::cout << "Graphics thread Core: " << GetCurrentProcessorNumber() << std::endl;

	while (m_threadRunning)
	{
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


			//onUpdate(deltaTime);
			//m_world->update(deltaTime);
			//m_inputSystem->update();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		
	}
}
*/

void Game::runPhysicsThread()
{
	SetThreadAffinityMask(GetCurrentThread(), PHYSICS_CORE_MASK);
	std::cout << "Physics thread Core: " << GetCurrentProcessorNumber() << std::endl;

	while (m_threadRunning)
	{
		auto loopStart = std::chrono::high_resolution_clock::now();

		{
			std::lock_guard<std::mutex> lock(m_dataMutex);
			m_physicsEngine->update();
		}

		auto loopMid = std::chrono::high_resolution_clock::now(); // after update
		float targetFrameTime = 1.0f / m_targetPhysicsHz;

		std::chrono::duration<float> workTime = loopMid - loopStart;
		float sleepTime = targetFrameTime - workTime.count();

		// Sleep if there's enough time to do it meaningfully
		if (sleepTime > 0.002f)
			std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime - 0.001f));

		// Spinlock the remainder to be more precise
		while (std::chrono::high_resolution_clock::now() - loopStart < std::chrono::duration<float>(targetFrameTime))
		{
			// tight loop
		}

		auto loopEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> totalLoopTime = loopEnd - loopStart;
		m_actualPhysicsHz = 1.0f / totalLoopTime.count();
	}
}

void Game::runNetworkingThread()
{
	SetThreadAffinityMask(GetCurrentThread(), NETWORKING_CORE_MASK);
	std::cout << "Networking thread Core: " << GetCurrentProcessorNumber() << std::endl;

	while (m_threadRunning)
	{
		auto loopStart = std::chrono::high_resolution_clock::now();

		{
			std::lock_guard<std::mutex> lock(m_dataMutex);
			// TODO: Add networking logic here
		}

		auto loopMid = std::chrono::high_resolution_clock::now();
		float targetFrameTime = 1.0f / m_targetNetworkingHz;

		std::chrono::duration<float> workTime = loopMid - loopStart;
		float sleepTime = targetFrameTime - workTime.count();

		if (sleepTime > 0.002f)
			std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime - 0.001f));

		while (std::chrono::high_resolution_clock::now() - loopStart < std::chrono::duration<float>(targetFrameTime))
		{
			// Busy wait
		}

		auto loopEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> totalLoopTime = loopEnd - loopStart;
		m_actualNetworkingHz = 1.0f / totalLoopTime.count();
	}
}

void Game::onInternalUpdate()
{
	static auto lastTime = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = now - lastTime;

	float frameDuration = 1.0f / m_targetGraphicsHz;
	if (elapsed.count() < frameDuration) return;

	m_actualGraphicsHz = 1.0f / elapsed.count();
	lastTime = now;
	std::cout << "Graphics Hz: " << m_actualGraphicsHz << std::endl;
	std::cout << "Target Graphics Hz: " << m_targetGraphicsHz << std::endl;
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
	m_graphicsEngine->update();
}

void Game::pausePhysicsThread()
{
	std::cout << "Physics thread pausing: " << m_physicsThread.get_id() << std::endl;
	m_threadRunning = false;
	if (m_physicsThread.joinable())
	{
		m_physicsThread.join();
	}
}
void Game::resumePhysicsThread()
{
	m_threadRunning = true;
	m_physicsThread = std::thread(&Game::runPhysicsThread, this);
	std::cout << "Physics thread resumed: " << m_physicsThread.get_id() << std::endl;
}
void Game::quit()
{
	m_isRunning = false;
	m_threadRunning = false;
}