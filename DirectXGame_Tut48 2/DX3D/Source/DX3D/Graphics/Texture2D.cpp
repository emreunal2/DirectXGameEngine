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

#include <DX3D/Graphics/Texture2D.h>
#include <DirectXTex.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>

Texture2D::Texture2D(const wchar_t* full_path, RenderSystem* system): m_system(system)
{
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, m_imageData);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(m_system->m_d3d_device.Get(), m_imageData.GetImages(),
			m_imageData.GetImageCount(), m_imageData.GetMetadata(), &m_texture);
		if (FAILED(res)) DX3DError("Texture not created successfully");

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = m_imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)m_imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		D3D11_SAMPLER_DESC sampler_desc = {};
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampler_desc.MinLOD = 0.0f;
		sampler_desc.MaxLOD = (FLOAT)m_imageData.GetMetadata().mipLevels;

		res = m_system->m_d3d_device->CreateSamplerState(&sampler_desc,&m_sampler_state);
		if (FAILED(res)) DX3DError("Texture not created successfully");

		res = m_system->m_d3d_device->CreateShaderResourceView(m_texture.Get(), &desc,
			&m_shader_res_view);
		if (FAILED(res)) DX3DError("Texture not created successfully");
	}
	else
	{
		DX3DError("Texture not created successfully");
	}

	m_size = Rect(0, 0, (i32)m_imageData.GetMetadata().width, (i32)m_imageData.GetMetadata().height);
}

Texture2D::Texture2D(const Rect& size, Texture2D::Type type, RenderSystem* system) : m_system(system)
{
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = size.width;
	tex_desc.Height = size.height;

	if (type == Texture2D::Type::Normal)
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (type == Texture2D::Type::RenderTarget)
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (type == Texture2D::Type::DepthStencil)
		tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	tex_desc.Usage = D3D11_USAGE_DEFAULT;

	if (type == Texture2D::Type::Normal)
		tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	else if (type == Texture2D::Type::RenderTarget)
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	else if (type == Texture2D::Type::DepthStencil)
		tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;


	auto hr = m_system->m_d3d_device->CreateTexture2D(&tex_desc, nullptr, (ID3D11Texture2D**)m_texture.GetAddressOf());
	if (FAILED(hr))
		DX3DError("Texture not created successfully");

	if (type == Texture2D::Type::RenderTarget)
	{
		hr = m_system->m_d3d_device->CreateShaderResourceView(this->m_texture.Get(), NULL, &this->m_shader_res_view);
		if (FAILED(hr))
			DX3DError("Texture not created successfully");

		hr = m_system->m_d3d_device->CreateRenderTargetView(this->m_texture.Get(), NULL, &this->m_render_target_view);
		if (FAILED(hr))
			DX3DError("Texture not created successfully");
	}
	else if (type == Texture2D::Type::DepthStencil)
	{
		hr = m_system->m_d3d_device->CreateDepthStencilView(this->m_texture.Get(), NULL, &this->m_depth_stencil_view);
		if (FAILED(hr))
			DX3DError("Texture not created successfully");
	}

	m_size = size;
	m_type = type;
}

Rect Texture2D::getSize()
{
	return m_size;
}

unsigned char* Texture2D::getPixels()
{
	return m_imageData.GetImages()->pixels;
}

ui32 Texture2D::getBitsPerPixel()
{
	return (ui32)DirectX::BitsPerPixel(m_imageData.GetMetadata().format);
}

