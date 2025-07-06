

#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <Windows.h>

void Game::setTimeScale(f32 timeScale)
{
	m_timeScale = timeScale;
}
void Game::setGravity(f32 gravity)
{
	m_gravity = gravity;
}
f32 Game::getGravity()
{
	return m_gravity;
}

void Game::run()
{
	onCreate();

	MSG msg = {};
	
	while (m_isRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		onInternalUpdate();
	}

	onQuit();
}


