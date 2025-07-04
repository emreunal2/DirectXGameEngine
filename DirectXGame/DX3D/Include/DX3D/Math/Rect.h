

#pragma once

class Rect
{
public:
	Rect() :width(0), height(0), left(0), top(0)
	{
	}
	Rect(i32 width, i32 height) :left(0), top(0), width(width), height(height)
	{
	}
	Rect(i32 left, i32 top, i32 width, i32 height) :left(left), top(top), width(width), height(height)
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