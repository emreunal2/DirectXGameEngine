

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Rect.h>
#include <chrono>
#include <Windows.h>

//threads
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>

struct DataBuffer {
	std::mutex mutex;
	std::condition_variable cv;
	bool dataUpdated = false;
};

class Game
{
public:
	Game();
	virtual ~Game();

	void setTimeScale(f32 timeScale);
	void setGravity(f32 gravity);
	float getGravity();
	void run();
	void quit();
	int m_targetGraphicsHz = 60;
	int m_targetPhysicsHz = 500;
	int m_targetNetworkingHz = 30;

	// Actual frequencies (shown on screen)
	std::atomic<float> m_actualGraphicsHz = 0.0f;
	std::atomic<float> m_actualPhysicsHz = 0.0f;
	std::atomic<float> m_actualNetworkingHz = 0.0f;
	f32 spawnerX = 0;
	f32 spawnerY = 0;
	f32 spawnerZ = 0;
	f32 spawnerRadius = 1;
	f32 spawnerElasticity = 0;
	f32 spawnerMass = 1;
	f32 spawnerDirectionX = 0;
	f32 spawnerDirectionY = 0;
	f32 spawnerDirectionZ = 0;
	f32 spawnerLenght = 0;
	int spawnerType = 0;
	f32 spawnerCubeSizeX = 1;
	f32 spawnerCubeSizeY = 1;
	f32 spawnerCubeSizeZ = 1;
	int numberOfObjects = 0;
	PhysicsEngine* getPhysicsEngine();
	GraphicsEngine* getGraphicsEngine();
	World* getWorld();
	InputSystem* getInputSystem();
	ResourceManager* getResourceManager();
	Display* getDisplay();
	bool isGraphicsReady() const { return m_graphicsReady.load(); }
	void pausePhysicsThread();
	void resumePhysicsThread();
protected:
	virtual void onCreate() {}
	virtual void onUpdate(f32 deltaTime) {}
	virtual void onQuit() {}

private:
	void onDisplaySize(const Rect& size);
	void onInternalUpdate();

	void runGraphicsThread();
	void runPhysicsThread();
	void runNetworkingThread();
private:
	std::unique_ptr<InputSystem> m_inputSystem;
	std::unique_ptr<PhysicsEngine> m_physicsEngine;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<Display> m_display;
	std::unique_ptr<ResourceManager> m_resourceManager;
	std::unique_ptr<World> m_world;

	std::thread m_graphicsThread;
	std::thread m_physicsThread;
	std::thread m_networkingThread;
	std::atomic<bool> m_threadRunning = true;
	std::atomic<bool> m_graphicsReady = false;

	bool m_isRunning = true;
	std::mutex m_dataMutex;

	std::chrono::system_clock::time_point m_previousTime;
	float m_totalTime = 0.0f;
	float m_timeScale = 1.0f;
	float m_gravity = 9.8f;

	const DWORD GRAPHICS_CORE_MASK = 0x2;
	const DWORD NETWORKING_CORE_MASK = 0x4;
	const DWORD PHYSICS_CORE_MASK = 0x1FFFF8;

	DataBuffer m_dataBuffer;
	friend class GraphicsEngine;
	friend class Display;
};

