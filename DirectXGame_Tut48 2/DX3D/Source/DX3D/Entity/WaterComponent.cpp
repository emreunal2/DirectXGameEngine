

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
	try {
		m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
	}
	catch (...)
	{
		// Handle any exceptions that may occur during cleanup
	}
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
	const ui32 waterWidth = 1024;
	const ui32 waterHeight = 1024;

	const ui32 maxX = waterWidth - 1;
	const ui32 maxY = waterHeight - 1;

	VertexMesh* waterVertices = new VertexMesh[waterWidth * waterHeight];
	ui32* waterIndices = new ui32[maxX * maxY * 6];

	ui32 index = 0;
	for (ui32 x = 0; x < waterWidth; ++x)
	{
		for (ui32 y = 0; y < waterHeight; ++y)
		{
			const f32 fx = (f32)x / (f32)maxX;
			const f32 fy = (f32)y / (f32)maxY;

			waterVertices[y * waterWidth + x] = {
				Vector3D(fx, 0.0f, fy),
				Vector2D(fx, fy),
				Vector3D(),
				Vector3D(),
				Vector3D()
			};

			if (x < maxX && y < maxY)
			{
				const ui32 base = y * waterWidth + x;

				waterIndices[index + 0] = (y + 1) * waterWidth + x;
				waterIndices[index + 1] = base;
				waterIndices[index + 2] = base + 1;

				waterIndices[index + 3] = base + 1;
				waterIndices[index + 4] = (y + 1) * waterWidth + (x + 1);
				waterIndices[index + 5] = (y + 1) * waterWidth + x;

				index += 6;
			}
		}
	}

	auto renderSystem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();
	m_meshVb = renderSystem->createVertexBuffer(waterVertices, sizeof(VertexMesh), waterWidth * waterHeight);
	m_meshIb = renderSystem->createIndexBuffer(waterIndices, maxX * maxY * 6);

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
