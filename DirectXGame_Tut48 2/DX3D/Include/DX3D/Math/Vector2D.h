#pragma once

class Vector2D
{
public:
	Vector2D() : x(0), y(0) {}
	Vector2D(f32 n_x, f32 n_y) : x(n_x), y(n_y) {}
	Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y) {}

	~Vector2D() {}

public:
	f32 x, y;
};

// === Non-member operators declared inline ===

inline Vector2D operator*(const Vector2D& vec, f32 num)
{
	return Vector2D(vec.x * num, vec.y * num);
}

inline Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x + b.x, a.y + b.y);
}

inline Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x - b.x, a.y - b.y);
}
