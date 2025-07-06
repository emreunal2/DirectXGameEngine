#pragma once
#include <DX3D/Math/Vector3D.h>

class Vector4D
{
public:
	Vector4D() : x(0), y(0), z(0), m_w(0) {}

	Vector4D(f32 n_x, f32 n_y, f32 n_z, f32 n_w)
		: x(n_x), y(n_y), z(n_z), m_w(n_w) {
	}

	Vector4D(const Vector4D& vector) = default;

	explicit Vector4D(const Vector3D& vector)
		: x(vector.getx()), y(vector.gety()), z(vector.getz()), m_w(1.0f) {
	}

	void cross(const Vector4D& v1, const Vector4D& v2, const Vector4D& v3)
	{
		this->x = v1.y * (v2.z * v3.m_w - v3.z * v2.m_w)
			- v1.z * (v2.y * v3.m_w - v3.y * v2.m_w)
			+ v1.m_w * (v2.y * v3.z - v2.z * v3.y);

		this->y = -(v1.x * (v2.z * v3.m_w - v3.z * v2.m_w)
			- v1.z * (v2.x * v3.m_w - v3.x * v2.m_w)
			+ v1.m_w * (v2.x * v3.z - v3.x * v2.z));

		this->z = v1.x * (v2.y * v3.m_w - v3.y * v2.m_w)
			- v1.y * (v2.x * v3.m_w - v3.x * v2.m_w)
			+ v1.m_w * (v2.x * v3.y - v3.x * v2.y);

		this->m_w = -(v1.x * (v2.y * v3.z - v3.y * v2.z)
			- v1.y * (v2.x * v3.z - v3.x * v2.z)
			+ v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

	~Vector4D() = default;

	inline f32 getx() const { return x; }
	inline f32 gety() const { return y; }
	inline f32 getz() const { return z; }
	inline f32 getm_w() const { return m_w; }

	inline void setx(f32 val) { x = val; }
	inline void sety(f32 val) { y = val; }
	inline void setz(f32 val) { z = val; }
	inline void setm_w(f32 val) { m_w = val; }

private:
	f32 x, y, z, m_w;
};
