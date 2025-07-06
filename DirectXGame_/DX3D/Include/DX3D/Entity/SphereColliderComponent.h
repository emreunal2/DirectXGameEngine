

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>


class SphereColliderComponent : public Component
{
public:
	SphereColliderComponent();
	virtual ~SphereColliderComponent();
	SphereColliderComponent(const SphereColliderComponent&) = delete;
	SphereColliderComponent& operator=(const SphereColliderComponent&) = delete;
	void setRadius(f32 radius);
	f32 getRadius();
protected:
	virtual void onCreateInternal() override;
private:
	f32 m_radius = 1.0f;
};

