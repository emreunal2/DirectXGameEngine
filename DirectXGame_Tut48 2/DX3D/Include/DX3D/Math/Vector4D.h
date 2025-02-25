/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#pragma once
#include <DX3D/Math/Vector3D.h>

class Vector4D
{
public:
	Vector4D() :x(0), y(0), z(0),m_w(0)
	{
	}
	Vector4D(f32 x, f32 y, f32 z,f32 w) :x(x), y(y), z(z), m_w(w)
	{
	}
	Vector4D(const Vector4D& vector) :x(vector.x), y(vector.y), z(vector.z), m_w(vector.m_w)
	{
	}
	Vector4D(const Vector3D& vector) :x(vector.x), y(vector.y), z(vector.z), m_w(1.0)
	{
	}

	void cross(Vector4D &v1, Vector4D &v2, Vector4D &v3)
	{
		this->x = v1.y * (v2.z * v3.m_w - v3.z * v2.m_w) - v1.z * (v2.y * v3.m_w - v3.y * v2.m_w) + v1.m_w * (v2.y * v3.z - v2.z *v3.y);
		this->y = -(v1.x * (v2.z * v3.m_w - v3.z * v2.m_w) - v1.z * (v2.x * v3.m_w - v3.x * v2.m_w) + v1.m_w * (v2.x * v3.z - v3.x * v2.z));
		this->z = v1.x * (v2.y * v3.m_w - v3.y * v2.m_w) - v1.y * (v2.x *v3.m_w - v3.x * v2.m_w) + v1.m_w * (v2.x * v3.y - v3.x * v2.y);
		this->m_w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x *v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

	~Vector4D()
	{
	}

public:
	f32 x, y, z,m_w;
};