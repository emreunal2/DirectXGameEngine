#pragma once
#include <DX3D/All.h>
#include "GameItem.h"

enum class MaterialType
{
	DEFAULT,
	GRASS,
	METAL,
};
class SphereItem : public GameItem
{
public:
	SphereItem();
	virtual ~SphereItem();
	f32 getMass();
	void setMass(f32 mass);
	void setElasticity(f32 elasticity);
	f32 getElasticity();
	void setMaterialType(MaterialType type);
	MaterialType getMaterialType();

protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);
	virtual void onCollisionEnter(Component* body1, Component* body2);
	//virtual void onCollisionStay(Component* body1, Component* body2);
	//virtual void onCollisionExit(Component* body1, Component* body2);
	virtual void ApplyMovement(f32 deltaTime);
	virtual void ApplyGravity(f32 deltaTime);
	virtual void ApplyRotation(f32 deltaTime);
	SphereColliderComponent* m_collider = nullptr;
	f32 m_mass;
	f32 m_elasticity = 1.0f;
	MaterialType m_materialType = MaterialType::DEFAULT;
	Vector3D m_angularVelocity = Vector3D(0, 0, 0);
	float m_inertia = 1.0f; // placeholder, set properly after mass & radius are known
};

