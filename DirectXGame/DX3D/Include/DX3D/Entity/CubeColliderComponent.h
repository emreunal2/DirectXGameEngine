#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>
class CubeColliderComponent : public Component
{
public:
	CubeColliderComponent();
	virtual ~CubeColliderComponent();

	void setExtents(const Vector3D& extents);
	Vector3D getExtents() const;
protected:
	virtual void onCreateInternal();
	Vector3D m_extents = Vector3D(1.0f, 1.0f, 1.0f);
};

