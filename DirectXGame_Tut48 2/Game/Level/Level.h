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
#include <DX3D/All.h>
#include "../UI/HUD/HUD.h"
#include "../UI/Screen/WinScreen.h"
#include "../UI/Screen/GameOverScreen.h"
#include <sstream>

class Level
{
public:
	Level(Game* game);
	~Level();

	Entity* getPlayer();
	void generateLevel();

	void onRestart();

	void onCreate();
	void onUpdate(f32 deltaTime);

private:
	Game* m_game = nullptr;

	std::unique_ptr<HUD> m_hud = nullptr;
	std::unique_ptr<WinScreen> m_winScreen = nullptr;
	std::unique_ptr<GameOverScreen> m_gameOverScreen = nullptr;
	
	Entity* m_entity = nullptr;
	Entity* m_player = nullptr;

	TerrainComponent* m_terrainComponent = nullptr;

	f32 m_rotation = 0.0f;

	f32 m_elapsedSecondsAsteroids = 0.0f;
	f32 m_elapsedSecondsScores = 0.0f;

	bool m_locked = true;

	f32 m_elapsedSecondsMatch = 0.0f;
	f32 m_maximumScore = 0.0f;
	f32 m_totalScore = 0.0f;
	f32 m_elapsedSecondsEnd = 0.0f;
	i32 m_levels = 1;

	i32 m_sceneType = 0;

	Entity* m_screen = nullptr;
	Entity* m_background = nullptr;
};

