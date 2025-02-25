

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
