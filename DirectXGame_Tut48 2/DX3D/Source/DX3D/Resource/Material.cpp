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

#include <DX3D/Resource/Material.h>
#include <DX3D/Graphics/VertexShader.h>
#include <DX3D/Graphics/PixelShader.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Resource/Texture.h>

Material::Material(const wchar_t* path, ResourceManager* manager): Resource(path,manager)
{
	auto rsys = manager->getGame()->getGraphicsEngine()->getRenderSystem();
	
	m_vertex_shader = rsys->createVertexShader(path,"vsmain");
	if (!m_vertex_shader) DX3DError("Material not created successfully");

	m_pixel_shader = rsys->createPixelShader(path, "psmain");
	if (!m_pixel_shader) DX3DError("Material not created successfully");

}

Material::Material(const MaterialPtr & material, ResourceManager* manager) : Resource(L"", manager)
{
	m_vertex_shader = material->m_vertex_shader;
	m_pixel_shader = material->m_pixel_shader;
}

void Material::addTexture(const TexturePtr & texture)
{
	m_vec_textures.push_back(texture->m_texture);
}

void Material::removeTexture(ui32 index)
{
	if (index >= this->m_vec_textures.size()) return;
	m_vec_textures.erase(m_vec_textures.begin() + index);
}

void Material::setData(void * data, ui32 size)
{
	auto rsys = m_manager->getGame()->getGraphicsEngine()->getRenderSystem();

	if (!m_constant_buffer)
		m_constant_buffer = rsys->createConstantBuffer(data, size);
	else
		m_constant_buffer->update(rsys->getImmediateDeviceContext(), data);
}

void Material::setCullMode(const CullMode& mode)
{
	m_cull_mode = mode;
}

CullMode Material::getCullMode()
{
	return m_cull_mode;
}
