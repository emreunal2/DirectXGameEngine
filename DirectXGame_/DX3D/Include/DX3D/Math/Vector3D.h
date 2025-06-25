#pragma once
#include <cmath> // for sqrt

class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(f32 n_x, f32 n_y, f32 n_z) : x(n_x), y(n_y), z(n_z) {}
	Vector3D(const Vector3D& vector) = default;
	~Vector3D() = default;

	Vector3D& operator+=(const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3D& operator-=(const Vector3D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline f32 getx() const { return x; }
	inline f32 gety() const { return y; }
	inline f32 getz() const { return z; }

	inline void setx(f32 val) { x = val; }
	inline void sety(f32 val) { y = val; }
	inline void setz(f32 val) { z = val; }

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, f32 delta)
	{
		return {
			start.x * (1.0f - delta) + end.x * delta,
			start.y * (1.0f - delta) + end.y * delta,
			start.z * (1.0f - delta) + end.z * delta
		};
	}

	static f32 length(const Vector3D& vec)
	{
		return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	}

	static Vector3D normalize(const Vector3D& vec)
	{
		auto len = length(vec);
		if (!len) return Vector3D();
		return { vec.x / len, vec.y / len, vec.z / len };
	}

	static Vector3D cross(const Vector3D& v1, const Vector3D& v2)
	{
		return {
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x)
		};
	}

private:
	f32 x, y, z;
};

// === Non-member operators ===

inline Vector3D operator*(const Vector3D& vec, f32 num)
{
	return Vector3D(vec.getx() * num, vec.gety() * num, vec.getz() * num);
}

inline Vector3D operator+(const Vector3D& a, const Vector3D& b)
{
	Vector3D result = a;
	result += b;
	return result;
}

inline Vector3D operator-(const Vector3D& a, const Vector3D& b)
{
	Vector3D result = a;
	result -= b;
	return result;
}
