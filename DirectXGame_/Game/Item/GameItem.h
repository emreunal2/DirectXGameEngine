

#pragma once
#include <DX3D/All.h>


class GameItem : public Entity
{
public:
	GameItem();
	virtual ~GameItem();
	GameItem(const GameItem&) = delete;
	GameItem& operator=(const GameItem&) = delete;
	void setPosition(const Vector3D& position);
	void setDirection(const Vector3D& direction);

protected:
	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;

public:
	MeshComponent* m_itemMesh = nullptr;
	SphereColliderComponent* m_collider = nullptr;

	Vector3D m_pos;
	Vector3D m_direction;
};

