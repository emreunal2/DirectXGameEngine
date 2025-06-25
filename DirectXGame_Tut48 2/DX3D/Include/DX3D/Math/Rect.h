#pragma once

class Rect
{
public:
	Rect() : width(0), height(0), left(0), top(0) {}
	Rect(i32 n_width, i32 n_height) : left(0), top(0), width(n_width), height(n_height) {}
	Rect(i32 n_left, i32 n_top, i32 n_width, i32 n_height) : left(n_left), top(n_top), width(n_width), height(n_height) {}

	Rect(const Rect& rect) = default;
	~Rect() = default;

	// Accessors
	i32 getWidth() const { return width; }
	void setWidth(i32 w) { width = w; }

	i32 getHeight() const { return height; }
	void setHeight(i32 h) { height = h; }

	i32 getLeft() const { return left; }
	void setLeft(i32 l) { left = l; }

	i32 getTop() const { return top; }
	void setTop(i32 t) { top = t; }

private:
	i32 width, height, left, top;
};
