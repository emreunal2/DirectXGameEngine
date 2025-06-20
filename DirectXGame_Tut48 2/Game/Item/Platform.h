#pragma once
#include <DX3D/All.h>
class Platform : public Entity
{
public:
	Platform();
	~Platform();
	Platform(const Platform&) = delete;
	Platform& operator=(const Platform&) = delete;
private:
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	f32 scale = 1.0f;
	MeshComponent* m_platformMesh = nullptr;
};
