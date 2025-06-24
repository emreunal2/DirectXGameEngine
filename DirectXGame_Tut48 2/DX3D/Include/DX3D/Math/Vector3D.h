

#pragma once

class Vector3D
{
public:
	Vector3D():x(0),y(0),z(0)
	{
	}
	Vector3D(f32 n_x,f32 n_y, f32 n_z) :x(n_x), y(n_y), z(n_z)
	{
	}
	Vector3D(const Vector3D& vector) :x(vector.x), y(vector.y), z(vector.z)
	{
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, f32 delta)
	{
		Vector3D v;
		v.x = start.x*(1.0f - delta) + end.x*(delta);
		v.y = start.y*(1.0f - delta) + end.y*(delta);
		v.z = start.z*(1.0f - delta) + end.z*(delta);
		return v;
	}

	static f32 length(const Vector3D& vec)
	{
		auto len = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
		return len;
	}
	static Vector3D normalize(const Vector3D& vec)
	{
		auto len = Vector3D::length(vec);
		if (!len)
			return Vector3D();
		Vector3D res;
		res.x = vec.x / len;
		res.y = vec.y / len;
		res.z = vec.z / len;

		return res;
	}

	static Vector3D cross(const Vector3D& v1, const Vector3D& v2)
	{
		Vector3D res;
		res.x = (v1.y * v2.z) - (v1.z * v2.y);
		res.y = (v1.z * v2.x) - (v1.x * v2.z);
		res.z = (v1.x * v2.y) - (v1.y * v2.x);
		return res;
	}

	~Vector3D()
	{
	}
	inline f32 getx() const { return x; }
	inline f32 gety() const { return y; }
	inline f32 getz() const { return z; }

	inline void setx(f32 val) { x = val; }
	inline void sety(f32 val) { y = val; }
	inline void setz(f32 val) { z = val; }
private:
	f32 x, y, z;
};

inline Vector3D operator*(const Vector3D& vec, f32 num)
{
	return Vector3D(vec.getx() * num, vec.gety() * num, vec.getz() * num);
}

inline Vector3D operator+(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(a.getx() + b.getx(), a.gety() + b.gety(), a.getz() + b.getz());
}

inline Vector3D operator-(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(a.getx() - b.getx(), a.gety() - b.gety(), a.getz() - b.getz());
}