#pragma once
#include <DX3D/All.h>
class Platform : public Entity
{
public:
	Platform();
	~Platform();

	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	f32 scale = 1.0f;
	MeshComponent* m_platformMesh = nullptr;
};
