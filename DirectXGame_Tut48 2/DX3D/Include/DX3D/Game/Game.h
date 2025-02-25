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


	friend class GraphicsEngine;
	friend class Display;
};

