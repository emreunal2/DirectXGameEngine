#pragma once
#include <DX3D/Math/Vector3D.h>
#include <DX3D/Math/Vector2D.h>

class VertexMesh
{
public:
	VertexMesh() : m_position(), m_texcoord(), m_normal(), m_tangent(), m_binormal() {}

	VertexMesh(const Vector3D& position, const Vector2D& texcoord, const Vector3D& normal,
		const Vector3D& tangent, const Vector3D& binormal)
		: m_position(position), m_texcoord(texcoord), m_normal(normal), m_tangent(tangent), m_binormal(binormal) {
	}

	VertexMesh(const VertexMesh& vertex) = default;
	~VertexMesh() = default;

private:
	Vector3D m_position;
	Vector2D m_texcoord;
	Vector3D m_normal;
	Vector3D m_tangent;
	Vector3D m_binormal;
};
