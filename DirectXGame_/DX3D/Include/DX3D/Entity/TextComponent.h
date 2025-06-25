

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Rect.h>


class TextComponent: public Component
{
public:
	TextComponent();
	virtual ~TextComponent();
	TextComponent(const TextComponent&) = delete;
	TextComponent& operator=(const TextComponent&) = delete;
	void setFont(const FontPtr& font);
	const FontPtr& getFont();

	void setText(const wchar_t* text);
	const wchar_t* getText();

	Rect getBounds();
protected:
	virtual void onCreateInternal() override;
private:
	std::wstring m_text = L"";
	FontPtr m_font;
};

