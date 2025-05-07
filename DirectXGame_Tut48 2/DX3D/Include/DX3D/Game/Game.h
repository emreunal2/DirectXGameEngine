

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Rect.h>
#include <chrono>


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

	PhysicsEngine* getPhysicsEngine();
	GraphicsEngine* getGraphicsEngine();
	World* getWorld();
	InputSystem* getInputSystem();
	ResourceManager* getResourceManager();
	Display* getDisplay();
protected:
	virtual void onCreate() {}
	virtual void onUpdate(f32 deltaTime) {}
	virtual void onQuit() {}

private:
	void onDisplaySize(const Rect& size);
	void onInternalUpdate();
private:
	std::unique_ptr<InputSystem> m_inputSystem;
	std::unique_ptr<PhysicsEngine> m_physicsEngine;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<Display> m_display;
	std::unique_ptr<ResourceManager> m_resourceManager;
	std::unique_ptr<World> m_world;

	bool m_isRunning = true;
	std::chrono::system_clock::time_point m_previousTime;
	float m_totalTime = 0.0f;
	float m_timeScale = 1.0f;
	float m_gravity = 9.8f;

	friend class GraphicsEngine;
	friend class Display;
};

