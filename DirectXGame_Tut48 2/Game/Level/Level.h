#pragma once
#include <DX3D/All.h>
#include "../UI/HUD/HUD.h"
#include "../UI/Screen/WinScreen.h"
#include "../UI/Screen/GameOverScreen.h"
#include <sstream>

enum class LightingMode
{
	Daylight,
	Torch
};

class Level
{
public:
	explicit Level(Game* game);
	~Level();
	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
	Entity* getPlayer();
	void generateLevel();

	void onRestart();

	void onCreate();
	void onUpdate(f32 deltaTime);

	void toggleLightingMode();
	void updateLighting();

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

	LightingMode m_lightingMode = LightingMode::Daylight;
	LightComponent* m_directionalLight = nullptr;
	LightComponent* m_spotLight = nullptr;
};

