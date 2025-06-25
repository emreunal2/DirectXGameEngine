

#pragma once
#include <DX3D/All.h>
#include "GameItem.h"

class BoxItem : public GameItem
{
public:
	BoxItem();
	virtual ~BoxItem();

protected:
	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;
	virtual void onCollision(Component* body1, Component* body2) override;

private:
	f32 m_angle = 0;
	f32 m_elapsedSeconds = 0.0f;
};

