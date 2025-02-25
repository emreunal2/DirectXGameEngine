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
#include <d3d11.h> 
#include <wrl.h>
#include <DX3D/Prerequisites.h>


class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem * system);

	void clearRenderTargetColor(const SwapChainPtr& swap_chain,f32 red, f32 green, f32 blue, f32 alpha);
	void clearDepthStencil(const SwapChainPtr& swap_chain);

	//void clearRenderTarget(const TexturePtr& render_target, f32 red, f32 green, f32 blue, f32 alpha);
	//void clearDepthStencil(const TexturePtr& depth_stencil);

	//void setRenderTarget(const TexturePtr& render_target, const TexturePtr& depth_stencil);
	//
	void setVertexBuffer(const VertexBufferPtr& vertex_buffer);
	void setIndexBuffer(const IndexBufferPtr& index_buffer);


	void drawTriangleList(ui32 vertex_count, ui32 start_vertex_index);
	void drawIndexedTriangleList(ui32 index_count, ui32 start_vertex_index, ui32 start_index_location);
	void drawTriangleStrip(ui32 vertex_count, ui32 start_vertex_index);

	void setViewportSize(ui32 width, ui32 height);

	void setVertexShader(const VertexShaderPtr& vertex_shader);
	void setPixelShader(const PixelShaderPtr& pixel_shader);

	//void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr* texture, ui32 num_textures);
	void setTexture(const Texture2DPtr* texture, ui32 num_textures);

	void setConstantBuffer(const ConstantBufferPtr& buffer);
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_device_context;
	RenderSystem * m_system = nullptr;
private:
	friend class ConstantBuffer;
};

