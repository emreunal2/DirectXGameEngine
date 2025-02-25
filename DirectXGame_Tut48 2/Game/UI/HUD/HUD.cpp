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

#include "HUD.h"
#include <sstream>

HUD::HUD(Game* game): m_game(game)
{
	auto font = m_game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");

	auto cross = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/cross2.png");

	auto levelBanner = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/level_banner.png");
	auto timeBanner = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/time_banner.png");
	auto scoreBanner = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/score_banner.png");
	auto totalScoreBanner = m_game->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/UI/totscore_banner.png");


	{
		m_levelBanner = m_game->getWorld()->createEntity<Entity>();
		auto image = m_levelBanner->createComponent<ImageComponent>();
		image->setImage(levelBanner);
		image->setSize({ 0,0,333,106 });
		m_levelBanner->getTransform()->setPosition(Vector3D(10, 10, 0));
	}

	{
		m_cross = m_game->getWorld()->createEntity<Entity>();
		auto image = m_cross->createComponent<ImageComponent>();
		image->setImage(cross);
		image->setSize({ 0,0,50,50 });
		m_cross->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_timeBanner = m_game->getWorld()->createEntity<Entity>();
		auto image = m_timeBanner->createComponent<ImageComponent>();
		image->setImage(timeBanner);
		image->setSize({ 0,0,225,105 });
		m_timeBanner->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_scoreBanner = m_game->getWorld()->createEntity<Entity>();
		auto image = m_scoreBanner->createComponent<ImageComponent>();
		image->setImage(scoreBanner);
		image->setSize({ 0,0,234,106 });
		m_scoreBanner->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_totScoreBanner = m_game->getWorld()->createEntity<Entity>();
		auto image = m_totScoreBanner->createComponent<ImageComponent>();
		image->setImage(totalScoreBanner);
		image->setSize({ 0,0,312,106 });
		m_totScoreBanner->getTransform()->setPosition(Vector3D(0, 0, 0));
	}





	{
		m_timeText = m_game->getWorld()->createEntity<Entity>();
		auto text = m_timeText->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"74 sec.");
		m_timeText->getTransform()->setPosition(Vector3D(0, 0, 0));
	}

	{
		m_levelText = m_game->getWorld()->createEntity<Entity>();
		auto text = m_levelText->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"1");
		m_levelText->getTransform()->setPosition(Vector3D(265, 45, 0));
	}

	{
		m_scoreText = m_game->getWorld()->createEntity<Entity>();
		auto text = m_scoreText->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"20 /40 boxes");
		m_scoreText->getTransform()->setPosition(Vector3D(10, 80, 0));
	}

	{
		m_totScoreText = m_game->getWorld()->createEntity<Entity>();
		auto text = m_totScoreText->createComponent<TextComponent>();
		text->setFont(font);
		text->setText(L"240 boxes");
		m_totScoreText->getTransform()->setPosition(Vector3D(10, 80, 0));
	}
}

HUD::~HUD()
{
	m_cross->release();

	m_timeBanner->release();
	m_levelBanner->release();
	m_scoreBanner->release();
	m_totScoreBanner->release();

	m_timeText->release();
	m_levelText->release();
	m_scoreText->release();
	m_totScoreText->release();
}

void HUD::setInfo(i32 level, i32 score, i32 maximumScore, i32 totalScore, i32 time)
{
	m_infoTextStr.str(std::wstring());
	m_infoTextStr << (i32)level;
	m_levelText->getComponent<TextComponent>()->setText(m_infoTextStr.str().c_str());

	m_infoTextStr.str(std::wstring());
	m_infoTextStr << (i32)score << L" / " << (i32)maximumScore << L" boxes";
	m_scoreText->getComponent<TextComponent>()->setText(m_infoTextStr.str().c_str());


	m_infoTextStr.str(std::wstring());
	m_infoTextStr << (i32)totalScore << L" boxes";
	m_totScoreText->getComponent<TextComponent>()->setText(m_infoTextStr.str().c_str());

	m_infoTextStr.str(std::wstring());
	m_infoTextStr << (i32)time << L" sec.";
	m_timeText->getComponent<TextComponent>()->setText(m_infoTextStr.str().c_str());
}


void HUD::onUpdate(f32 deltaTime)
{
	auto clientSize = m_game->getDisplay()->getClientSize();

	m_cross->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.width / 2.0f) - 25.0f,
		(f32)(clientSize.height / 2.0f) - 25.0f,
		0
	));
	m_scoreBanner->getTransform()->setPosition(Vector3D(
		(f32) 10.0f,
		(f32) (clientSize.height) - 220.0f,
		0
	));
	m_scoreText->getTransform()->setPosition(Vector3D(
		(f32) 150.0f,
		(f32) clientSize.height - 180.0f,
		0
	));

	m_totScoreBanner->getTransform()->setPosition(Vector3D(
		(f32)10.0f,
		(f32)(clientSize.height) - 110.0f,
		0
	));
	m_totScoreText->getTransform()->setPosition(Vector3D(
		(f32)150.0f,
		(f32)clientSize.height - 70.0f,
		0
	));

	m_timeBanner->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.width) - 340.0f,
		(f32)10,
		0
	));
	m_timeText->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.width) - 200.0f,
		(f32)60,
		0
	));
}



