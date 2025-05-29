#pragma once
#include <DX3D/All.h>
#include "GameItem.h"

class StaticSphereItem : public GameItem
{
public:
	StaticSphereItem();
	virtual ~StaticSphereItem();

protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);
	SphereColliderComponent* m_collider = nullptr;
};

