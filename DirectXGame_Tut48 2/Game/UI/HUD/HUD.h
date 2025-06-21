

#pragma once
#include <DX3D/All.h>
#include <sstream>

class HUD
{
public:
	explicit HUD(Game* game);
	~HUD();
	HUD(const HUD&) = delete;
	HUD& operator=(const HUD&) = delete;
	void setInfo(i32 level,i32 score, i32 totalScore, i32 time);
	virtual void onUpdate(f32 deltaTime);
private:
	Game* m_game = nullptr;

	Entity* m_cross = nullptr;

	Entity* m_timeBanner = nullptr;
	Entity* m_levelBanner = nullptr;
	Entity* m_scoreBanner = nullptr;
	Entity* m_totScoreBanner = nullptr;

	Entity* m_timeText = nullptr;
	Entity* m_levelText = nullptr;
	Entity* m_scoreText = nullptr;
	Entity* m_totScoreText = nullptr;

	std::wstringstream m_infoTextStr;
};

