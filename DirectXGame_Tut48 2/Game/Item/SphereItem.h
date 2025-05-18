#pragma once
#include <DX3D/All.h>
#include "GameItem.h"
class SphereItem : public GameItem
{
public:
	SphereItem();
	virtual ~SphereItem();
	f32 getMass();
	void setMass(f32 mass);
	void setElasticity(f32 elasticity);
	f32 getElasticity();

protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);
	virtual void onCollisionEnter(Component* body1, Component* body2);
	//virtual void onCollisionStay(Component* body1, Component* body2);
	//virtual void onCollisionExit(Component* body1, Component* body2);
	virtual void ApplyMovement(f32 deltaTime);
	virtual void ApplyGravity(f32 deltaTime);
	SphereColliderComponent* m_collider = nullptr;
	f32 m_mass;
	f32 m_elasticity = 1.0f;
};

