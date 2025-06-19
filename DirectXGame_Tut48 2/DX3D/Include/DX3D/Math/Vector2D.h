

#pragma once

class Vector2D
{
public:
	Vector2D() :x(0), y(0)
	{
	}
	Vector2D(f32 n_x, f32 n_y) :x(n_x), y(n_y)
	{
	}
	Vector2D(const Vector2D& vector) :x(vector.x), y(vector.y)
	{
	}

	Vector2D operator *(f32 num) const
	{
		return Vector2D(x*num, y*num);
	}

	Vector2D operator +(const Vector2D& vec) const
	{
		return Vector2D(x + vec.x, y + vec.y);
	}


	Vector2D operator -(const Vector2D& vec) const
	{
		return Vector2D(x - vec.x, y - vec.y);
	}


	~Vector2D()
	{
	}

public:
	f32 x, y;
};