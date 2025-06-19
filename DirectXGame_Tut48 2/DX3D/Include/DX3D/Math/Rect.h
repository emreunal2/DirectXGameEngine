

#pragma once

class Rect
{
public:
	Rect() :width(0), height(0), left(0), top(0)
	{
	}
	Rect(i32 n_width, i32 n_height) :left(0), top(0), width(n_width), height(n_height)
	{
	}
	Rect(i32 n_left, i32 n_top, i32 n_width, i32 n_height) :left(n_left), top(n_top), width(n_width), height(n_height)
	{
	}
	Rect(const Rect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height)
	{
	}
	~Rect()
	{
	}
public:
	i32 width, height, left, top;
};