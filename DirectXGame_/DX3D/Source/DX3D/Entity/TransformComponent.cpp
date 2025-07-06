

#include <DX3D/Entity/TransformComponent.h>

TransformComponent::TransformComponent() = default;

TransformComponent::~TransformComponent() = default;

void TransformComponent::setPosition(const Vector3D& position)
{
	m_position = position;
	updateWorldMatrix();
}

const Vector3D& TransformComponent::getPosition() const
{
	return m_position;
}

void TransformComponent::setRotation(const Vector3D& rotation)
{
	m_rotation = rotation;
	updateWorldMatrix();
}

const Vector3D& TransformComponent::getRotation() const
{
	return m_rotation;
}

void TransformComponent::setScale(const Vector3D& scale)
{
	m_scale = scale;
	updateWorldMatrix();
}

const Vector3D& TransformComponent::getScale() const
{
	return m_scale;
}

const Vector3D& TransformComponent::getDirection() const
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
	temp.setRotationX(m_rotation.getx());
	rot *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rotation.gety());
	rot *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_rotation.getz());
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
