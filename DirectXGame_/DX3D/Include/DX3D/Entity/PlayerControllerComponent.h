

#pragma once
#include <DX3D/Entity/Component.h>
#include <DX3D/Math/Vector3D.h>


class PlayerControllerComponent: public Component
{
public:
	PlayerControllerComponent();
	virtual ~PlayerControllerComponent();
	PlayerControllerComponent(const PlayerControllerComponent&) = delete;
	PlayerControllerComponent& operator=(const PlayerControllerComponent&) = delete;
	void setHeight(f32 height);
	f32 getHeight();

	const Vector3D& getMoveDirection() const;
	f32 getMoveDistance();

	void move(const Vector3D& direction, f32 distance);

protected:
	virtual void onCreateInternal() override;
private:
	f32 m_height = 1.8f;
	f32 m_distance = 0.0f;
	Vector3D m_direction;
};

