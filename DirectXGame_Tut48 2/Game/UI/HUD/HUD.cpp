

#include "HUD.h"
#include <sstream>

HUD::HUD(Game* game): m_game(game)
{
	auto font = m_game->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");

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
		text->setText(L"20 boxes");
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
	try {
		m_timeText->release();
		m_levelText->release();
		m_scoreText->release();
		m_totScoreText->release();
	}
	catch(...) {
		// Handle exceptions if necessary
	}
}

void HUD::setInfo(i32 level, i32 score, i32 maximumScore, i32 totalScore, i32 time)
{
	m_infoTextStr.str(std::wstring());
	m_infoTextStr << (i32)level;
	m_levelText->getComponent<TextComponent>()->setText(m_infoTextStr.str().c_str());

	m_infoTextStr.str(std::wstring());
	m_infoTextStr << (i32)score;
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

	m_scoreText->getTransform()->setPosition(Vector3D(
		(f32) 150.0f,
		(f32) clientSize.height - 180.0f,
		0
	));
	m_totScoreText->getTransform()->setPosition(Vector3D(
		(f32)150.0f,
		(f32)clientSize.height - 70.0f,
		0
	));
	m_timeText->getTransform()->setPosition(Vector3D(
		(f32)(clientSize.width) - 200.0f,
		(f32)60,
		0
	));
}



