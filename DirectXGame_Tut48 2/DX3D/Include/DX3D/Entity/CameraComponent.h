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
#include <DX3D/Prerequisites.h>
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Rect.h>
#include <DX3D/Math/Matrix4x4.h>


class CameraComponent: public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();

	void getViewMatrix(Matrix4x4& view);
	void getProjectionMatrix(Matrix4x4& proj);


	void setFarPlane(f32 farPlane);
	f32 getFarPlane();

	void setNearPlane(f32 nearPlane);
	f32 getNearPlane();

	void setFieldOfView(f32 fieldOfView);
	f32 getFieldOfView();

	void setType(const CameraType& type);
	CameraType getType();

	void setScreenArea(const Rect& area);
	Rect getScreenArea();

private:
	void computeProjectionMatrix();
protected:
	virtual void onCreateInternal();
private:
	Matrix4x4 m_projection;

	f32 m_nearPlane = 0.01f;
	f32 m_farPlane = 100.0f;
	f32 m_fieldOfView = 1.3f;
	CameraType m_type = CameraType::Perspective;
	Rect m_screenArea;
};

