

#pragma once
#include <d3d11.h> 
#include <wrl.h>
#include <DX3D/Prerequisites.h>

class SwapChain
{
public:
	//Initialize SwapChain for a window
	SwapChain(HWND hwnd,ui32 width,ui32 height,RenderSystem * system);
	SwapChain(const SwapChain&) = delete;
	SwapChain& operator=(const SwapChain&) = delete;
	void setFullScreen(bool fullscreen, ui32 width, ui32 height);
	void resize(ui32 width, ui32 height);
	bool present(bool vsync);

private:
	void reloadBuffers(ui32 width, ui32 height);
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swap_chain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_dsv = nullptr;
	RenderSystem * m_system = nullptr;

private:
	friend class DeviceContext;
};

