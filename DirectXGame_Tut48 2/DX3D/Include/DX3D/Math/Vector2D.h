#pragma once

class Vector2D
{
public:
	Vector2D() : x(0), y(0) {}
	Vector2D(f32 n_x, f32 n_y) : x(n_x), y(n_y) {}
	Vector2D(const Vector2D& vector) = default;

	Vector2D& operator+=(const Vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	~Vector2D() = default;

public:
	f32 x, y;
};

inline Vector2D operator*(const Vector2D& vec, f32 num)
{
	return Vector2D(vec.x * num, vec.y * num);
}

inline Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
	Vector2D result = a;
	result += b;
	return result;
}

inline Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
	Vector2D result = a;
	result -= b;
	return result;
}
