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

