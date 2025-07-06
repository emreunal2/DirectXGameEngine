

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>


class SphereColliderComponent : public Component
{
public:
	SphereColliderComponent();
	virtual ~SphereColliderComponent();

	void setRadius(f32 radius);
	f32 getRadius();

	void setLength(f32 length);
	f32 getLength();
protected:
	virtual void onCreateInternal();
private:
	f32 m_radius = 1.0f;
	f32 m_length = 0.0f;
};

