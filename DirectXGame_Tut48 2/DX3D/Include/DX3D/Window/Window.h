

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Rect.h>



class Window
{
public:
	Window();
	virtual ~Window();

	Rect getClientSize();
	Rect getScreenSize();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
	virtual void onSize(const Rect& size);

protected:
	void* m_hwnd;
	Rect m_size = { 0,0,1440,900 };
};

