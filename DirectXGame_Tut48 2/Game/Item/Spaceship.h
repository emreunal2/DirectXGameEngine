

#pragma once
#include <DX3D/All.h>

class Spaceship : public Entity
{
public:
	Spaceship();
	~Spaceship();
	Spaceship(const Spaceship&) = delete;
	Spaceship& operator=(const Spaceship&) = delete;
	f32 getScore();

	virtual void onCreate() override;
	virtual void onUpdate(f32 deltaTime) override;
	virtual void onCollision(Component* body1, Component* body2) override;

private:
	f32 m_pitch = 0.0f;
	f32 m_yaw = 0.0f;

	f32 m_oldPitch = 0;
	f32 m_oldYaw = 0;

	f32 m_camPitch = 0;
	f32 m_camYaw = 0;

	f32 m_oldCamPitch = 0;
	f32 m_oldCamYaw = 0;

	f32 m_forward = 0;

	bool m_turbo_mode = false;
	bool m_jump = false;
	f32 m_cam_distance = 18.0f;
	f32 m_current_cam_distance = 120.0f;

	f32 m_zoomSpeed = 50.0f;
	MeshComponent* m_spaceshipMesh = nullptr;
	CameraComponent* m_camera = nullptr;
	Entity* m_cameraEntity = nullptr;
	Entity* m_circleEntity = nullptr;

	PlayerControllerComponent* m_player = nullptr;

	f32 m_elapsedSecondsProjectile = 0.5f;


	f32 m_health = 50.0f;
	f32 m_ammo = 50.0f;

	f32 m_score = 0.0f;

};

