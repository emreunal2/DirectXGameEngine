

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Rect.h>
#include <d3d11.h> 
#include <wrl.h>
#include <DirectXTex.h>





class Texture2D
{
public:
	enum class Type
	{
		Normal = 0,
		RenderTarget,
		DepthStencil
	};
public:
	Texture2D(const wchar_t* full_path, RenderSystem* system);
	Texture2D(const Rect& size, Texture2D::Type type, RenderSystem* system);
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Rect getSize();
	unsigned char* getPixels();
	ui32 getBitsPerPixel();
private:
	Microsoft::WRL::ComPtr<ID3D11Resource> m_texture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shader_res_view = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler_state = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_render_target_view = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depth_stencil_view = nullptr;

	Texture2D::Type m_type = Texture2D::Type::Normal;

	Rect m_size;
	DirectX::ScratchImage m_imageData;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
	friend class RenderSystem;
};

