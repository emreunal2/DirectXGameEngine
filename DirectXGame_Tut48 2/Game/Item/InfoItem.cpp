

#include "InfoItem.h"

InfoItem::InfoItem()
{
}

InfoItem::~InfoItem()
{
}

void InfoItem::setText(const wchar_t* text)
{
	m_text->setText(text);
}



void InfoItem::onCreate()
{
	Entity::onCreate();
	auto font = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Font>(L"Assets/Fonts/Bahnschrift.font");
	m_text = createComponent<TextComponent>();
	m_text->setFont(font);

	auto clientSize = getWorld()->getGame()->getDisplay()->getClientSize();
	
	getTransform()->setPosition(Vector3D(
		(f32)(clientSize.getWidth() / 2.0f) + 20.0f,
		(f32)(clientSize.getHeight() / 2.0f) - 20.0f,
		0
	));
}

void InfoItem::onUpdate(f32 deltaTime)
{
	Entity::onUpdate(deltaTime);

	m_time += deltaTime;
	m_pos += 80.0f*deltaTime;

	auto clientSize = getWorld()->getGame()->getDisplay()->getClientSize();

	getTransform()->setPosition(Vector3D(
		(f32)(clientSize.getWidth() / 2.0f) - 20.0f ,
		(f32)(clientSize.getHeight() / 2.0f) - 60.0f - m_pos,
		0
	));

	if (m_time > 1.5f)
		release();
}
