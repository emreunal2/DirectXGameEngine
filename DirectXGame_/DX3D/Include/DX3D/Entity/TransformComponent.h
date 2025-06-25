

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>
#include <DX3D/Math/Matrix4x4.h>


class TransformComponent: public Component
{
public:
	TransformComponent();
	virtual ~TransformComponent();

	void setPosition(const Vector3D& position);
	const Vector3D& getPosition() const;

	void setRotation(const Vector3D& rotation);
	const Vector3D& getRotation() const;

	void setScale(const Vector3D& scale);
	const Vector3D& getScale() const;

	const Vector3D& getDirection() const;

	void getWorldMatrix(Matrix4x4& mat);

protected:
	void updateWorldMatrix();
private:
	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_scale = Vector3D(1,1,1);
	Vector3D m_direction;


	Matrix4x4 m_worldMat;
};

