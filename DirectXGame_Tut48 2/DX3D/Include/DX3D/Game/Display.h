

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Rect.h>
#include <DX3D/Window/Window.h>


class Display: public Window
{
public:
	explicit Display(Game* game);
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;
	~Display();

	void setFullScreen(const Rect& size, bool fullscreen);

protected:
	virtual void onSize(const Rect& size);
private:
	SwapChainPtr m_swapChain;
	Game* m_game = nullptr;

	friend class GraphicsEngine;
};

