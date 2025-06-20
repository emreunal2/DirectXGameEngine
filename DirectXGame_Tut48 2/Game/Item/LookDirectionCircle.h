#pragma once
#include <DX3D/All.h>
class LookDirectionCircle : public Entity
{
public:
	LookDirectionCircle();
	~LookDirectionCircle();
	LookDirectionCircle(const LookDirectionCircle&) = delete;
	LookDirectionCircle& operator=(const LookDirectionCircle&) = delete;
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
private:
	MeshComponent* m_circleMesh = nullptr;
};