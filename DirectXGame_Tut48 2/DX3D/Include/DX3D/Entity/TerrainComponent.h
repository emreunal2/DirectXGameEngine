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
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>



class TerrainComponent: public Component
{
public:
	TerrainComponent();
	virtual ~TerrainComponent();

	void setHeightMap(const TexturePtr& heightMap);
	const TexturePtr& getHeightMap();

	void setGroundMap(const TexturePtr& groundMap);
	const TexturePtr& getGroundMap();

	void setCliffMap(const TexturePtr& cliffMap);
	const TexturePtr& getCliffMap();

	void setSize(const Vector3D& size);
	Vector3D getSize();

	f32 getHeightFromWorldPoint(const Vector3D& worldPoint);

	bool intersect(const Vector3D& pos, const Vector3D& dir, f32 distance, f32 minDistance, Vector3D& res);

private:
	void generateTerrainMesh();
	void updateData(void* data, ui32 size);
protected:
	virtual void onCreateInternal();
private:
	TexturePtr m_heightMap;
	TexturePtr m_groundMap;
	TexturePtr m_cliffMap;

	Vector3D m_size = Vector3D(512, 100, 512);

	VertexBufferPtr m_meshVb;
	IndexBufferPtr m_meshIb;
	ConstantBufferPtr m_cb;

	VertexShaderPtr m_vertexShader;
	PixelShaderPtr m_pixelShader;

	friend class GraphicsEngine;
};

