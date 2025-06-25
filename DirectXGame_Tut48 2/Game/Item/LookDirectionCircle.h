#pragma once
#include <DX3D/All.h>
class LookDirectionCircle : public Entity
{
public:
	LookDirectionCircle();
	~LookDirectionCircle();
	LookDirectionCircle(const LookDirectionCircle&) = delete;
	LookDirectionCircle& operator=(const LookDirectionCircle&) = delete;
	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;
private:
	MeshComponent* m_circleMesh = nullptr;
};