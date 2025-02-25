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
		(f32)(clientSize.width / 2.0f) + 20.0f,
		(f32)(clientSize.height / 2.0f) - 20.0f,
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
		(f32)(clientSize.width / 2.0f) - 20.0f ,
		(f32)(clientSize.height / 2.0f) - 60.0f - m_pos,
		0
	));

	if (m_time > 1.5f)
		release();
}
