

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>


class WaterComponent : public Component
{
public:
	WaterComponent();
	virtual ~WaterComponent();
	WaterComponent(const WaterComponent&) = delete;
	WaterComponent& operator=(const WaterComponent&) = delete;
	void setWaveHeightMap(const TexturePtr& heightMap);
	const TexturePtr& getWaveHeightMap();

	void setSize(const Vector3D& size);
	Vector3D getSize();


private:
	void generateMesh();
	void updateData(void* data, ui32 size);

protected:
	virtual void onCreateInternal() override;

private:
	TexturePtr m_waveHeightMap;

	Vector3D m_size = Vector3D(2048, 8, 2048);

	VertexBufferPtr m_meshVb;
	IndexBufferPtr m_meshIb;
	ConstantBufferPtr m_cb;

	VertexShaderPtr m_vertexShader;
	PixelShaderPtr m_pixelShader;

	friend class GraphicsEngine;
};

