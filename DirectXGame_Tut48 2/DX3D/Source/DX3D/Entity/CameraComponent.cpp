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

#include <DX3D/Entity/CameraComponent.h>
#include <DX3D/Entity/TransformComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>


CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void CameraComponent::getViewMatrix(Matrix4x4& view)
{
	m_entity->getTransform()->getWorldMatrix(view);
	view.inverse();
}

void CameraComponent::getProjectionMatrix(Matrix4x4& proj)
{
	proj = m_projection;
}

void CameraComponent::setFarPlane(f32 farPlane)
{
	m_farPlane = farPlane;
	computeProjectionMatrix();
}

f32 CameraComponent::getFarPlane()
{
	return m_farPlane;
}

void CameraComponent::setNearPlane(f32 nearPlane)
{
	m_nearPlane = nearPlane;
	computeProjectionMatrix();
}

f32 CameraComponent::getNearPlane()
{
	return m_nearPlane;
}

void CameraComponent::setFieldOfView(f32 fieldOfView)
{
	m_fieldOfView = fieldOfView;
	computeProjectionMatrix();
}

f32 CameraComponent::getFieldOfView()
{
	return m_fieldOfView;
}

void CameraComponent::setType(const CameraType& type)
{
	m_type = type;
	computeProjectionMatrix();
}

CameraType CameraComponent::getType()
{
	return m_type;
}

void CameraComponent::setScreenArea(const Rect& area)
{
	m_screenArea = area;
	computeProjectionMatrix();
}

Rect CameraComponent::getScreenArea()
{
	return m_screenArea;
}

void CameraComponent::computeProjectionMatrix()
{
	if (m_type == CameraType::Perspective)
		m_projection.setPerspectiveFovLH(m_fieldOfView, (f32)m_screenArea.width / (f32)m_screenArea.height,
			m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection.setOrthoLH((f32)m_screenArea.width, (f32)m_screenArea.height, m_nearPlane, m_farPlane);
}

void CameraComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
