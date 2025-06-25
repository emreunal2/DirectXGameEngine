

#include <DX3D/Entity/CameraComponent.h>
#include <DX3D/Entity/TransformComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>


CameraComponent::CameraComponent() = default;

CameraComponent::~CameraComponent()
{
	try
	{
		m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
	}
	catch (...)
	{
		// Log error, or silently suppress (not ideal, but safe for destructors)
	}
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

const Rect& CameraComponent::getScreenArea() const
{
	return m_screenArea;
}

void CameraComponent::computeProjectionMatrix()
{
	if (m_type == CameraType::Perspective)
		m_projection.setPerspectiveFovLH(m_fieldOfView, (f32)m_screenArea.getWidth() / (f32)m_screenArea.getHeight(),
			m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection.setOrthoLH((f32)m_screenArea.getWidth(), (f32)m_screenArea.getHeight(), m_nearPlane, m_farPlane);
}

void CameraComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
