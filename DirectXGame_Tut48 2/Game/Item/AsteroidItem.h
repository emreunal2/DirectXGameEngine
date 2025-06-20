

#pragma once
#include <DX3D/All.h>
#include "GameItem.h"

class AsteroidItem : public GameItem
{
public:
	AsteroidItem();
	virtual ~AsteroidItem();

	void setPosition(const Vector3D& position);
	void setDirection(const Vector3D& direction);
	void setSpeed(f32 speed);

protected:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);
private:
	f32 m_angle = 0;
	f32 m_speed = 142.0f;
	f32 m_elapsedSecondsLastUpdate = 0.0f;
};

