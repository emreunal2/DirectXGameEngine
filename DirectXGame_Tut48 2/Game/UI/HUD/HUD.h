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
#include <sstream>

class HUD
{
public:
	HUD(Game* game);
	~HUD();

	void setInfo(i32 level,i32 score, i32 maximumScore, i32 totalScore, i32 time);
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

