#pragma once
#include <DX3D/All.h>
#include "GameItem.h"

class StaticCubeItem : public GameItem
{
public:
	StaticCubeItem();
	virtual ~StaticCubeItem();
protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);
	virtual void onCollisionEnter(Component* body1, Component* body2);
	//virtual void onCollisionStay(Component* body1, Component* body2);
	//virtual void onCollisionExit(Component* body1, Component* body2);
	//SphereColliderComponent* m_collider = nullptr;
	CubeColliderComponent* m_collider = nullptr;
};

