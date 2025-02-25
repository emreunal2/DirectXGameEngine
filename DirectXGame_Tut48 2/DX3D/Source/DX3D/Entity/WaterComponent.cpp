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

#include <DX3D/Entity/WaterComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/ConstantBuffer.h>

#include <DX3D/Math/VertexMesh.h>

WaterComponent::WaterComponent()
{
}

WaterComponent::~WaterComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void WaterComponent::setWaveHeightMap(const TexturePtr& heightMap)
{
	m_waveHeightMap = heightMap;
}

const TexturePtr& WaterComponent::getWaveHeightMap()
{
	return m_waveHeightMap;
}

void WaterComponent::setSize(const Vector3D& size)
{
	m_size = size;
}

Vector3D WaterComponent::getSize()
{
	return m_size;
}



void WaterComponent::generateMesh()
{
	const ui32 w = 1024;
	const ui32 h = 1024;

	const ui32 ww = w - 1;
	const ui32 hh = h - 1;


	VertexMesh* terrainMeshVertices = new VertexMesh[w * h];
	ui32* terrainMeshIndices = new ui32[ww * hh * 6];

	auto i = 0;
	for (ui32 x = 0; x < w; x++)
	{
		for (ui32 y = 0; y < h; y++)
		{
			terrainMeshVertices[y * w + x] = {
				Vector3D((f32)x / (f32)ww,0,(f32)y / (f32)hh),
				Vector2D((f32)x / (f32)ww,(f32)y / (f32)hh),
				Vector3D(),
				Vector3D(),
				Vector3D()
			};

			if (x < ww && y < hh)
			{
				terrainMeshIndices[i] = (y + 1) * w + (x);
				terrainMeshIndices[i + 1] = (y)*w + (x);
				terrainMeshIndices[i + 2] = (y)*w + (x + 1);

				terrainMeshIndices[i + 3] = (y)*w + (x + 1);
				terrainMeshIndices[i + 4] = (y + 1) * w + (x + 1);
				terrainMeshIndices[i + 5] = (y + 1) * w + (x);
				i += 6;
			}
		}
	}

	auto renderSystem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();
	m_meshVb = renderSystem->createVertexBuffer(terrainMeshVertices, sizeof(VertexMesh), w * h);
	m_meshIb = renderSystem->createIndexBuffer(terrainMeshIndices, ww * hh * 6);

	m_vertexShader = renderSystem->createVertexShader(L"Assets/Shaders/Water.hlsl", "vsmain");
	m_pixelShader = renderSystem->createPixelShader(L"Assets/Shaders/Water.hlsl", "psmain");
}

void WaterComponent::updateData(void* data, ui32 size)
{
	auto renderSystem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();

	if (!m_cb)
		m_cb = renderSystem->createConstantBuffer(data, size);
	else
		m_cb->update(renderSystem->getImmediateDeviceContext(), data);
}

void WaterComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
	generateMesh();
}
