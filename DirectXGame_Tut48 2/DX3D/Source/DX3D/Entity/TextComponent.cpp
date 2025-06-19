


#include <DX3D/Entity/TextComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/Font2D.h>
#include <DX3D/Resource/Font.h>



TextComponent::TextComponent()
{
}

TextComponent::~TextComponent()
{
	try {
		m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
	}
	catch (...) {
		// Handle any exceptions that may occur during cleanup
	}
}

void TextComponent::setFont(const FontPtr& font)
{
	m_font = font;
}

const FontPtr& TextComponent::getFont()
{
	return m_font;
}

void TextComponent::setText(const wchar_t* text)
{
	m_text = text;
}

const wchar_t* TextComponent::getText()
{
	return m_text.c_str();
}

Rect TextComponent::getBounds()
{
	return m_font->getFont()->getBounds(m_text.c_str());
}

void TextComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
