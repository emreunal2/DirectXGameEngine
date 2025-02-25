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

#include <DX3D/Entity/TransformComponent.h>

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setPosition(const Vector3D& position)
{
	m_position = position;
	updateWorldMatrix();
}

Vector3D TransformComponent::getPosition()
{
	return m_position;
}

void TransformComponent::setRotation(const Vector3D& rotation)
{
	m_rotation = rotation;
	updateWorldMatrix();
}

Vector3D TransformComponent::getRotation()
{
	return m_rotation;
}

void TransformComponent::setScale(const Vector3D& scale)
{
	m_scale = scale;
	updateWorldMatrix();
}

Vector3D TransformComponent::getScale()
{
	return m_scale;
}

Vector3D TransformComponent::getDirection()
{
	return m_direction;
}

void TransformComponent::getWorldMatrix(Matrix4x4& mat)
{
	mat.setMatrix(m_worldMat);
}

void TransformComponent::updateWorldMatrix()
{
	Matrix4x4 temp,rot;

	m_worldMat.setIdentity();
	rot.setIdentity();
	
	temp.setIdentity();
	temp.setRotationX(m_rotation.x);
	rot *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rotation.y);
	rot *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_rotation.z);
	rot *= temp;

	m_direction = rot.getZDirection();


	temp.setIdentity();
	temp.setScale(m_scale);
	m_worldMat *= temp;

	m_worldMat *= rot;

	temp.setIdentity();
	temp.setTranslation(m_position);
	m_worldMat *= temp;
}
