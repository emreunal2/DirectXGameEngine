

#pragma once
#include <DX3D/All.h>

class InfoItem : public Entity
{
public:
	InfoItem();
	virtual ~InfoItem();
	InfoItem(const InfoItem&) = delete;
	InfoItem& operator=(const InfoItem&) = delete;

	void setText(const wchar_t* text);

protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	TextComponent* m_text = nullptr;
	f32 m_time = 0.0f;
	f32 m_pos = 0.0f;
};

