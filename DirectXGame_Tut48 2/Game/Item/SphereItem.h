#pragma once
#include <DX3D/All.h>
#include "GameItem.h"
class SphereItem : public GameItem
{
public:
	SphereItem();
	virtual ~SphereItem();


protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);
	virtual void ApplyMovement(f32 deltaTime);
	virtual void ApplyGravity();
};

