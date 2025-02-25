/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#pragma once
#include <DX3D/All.h>

class Spaceship : public Entity
{
public:
	Spaceship();
	~Spaceship();

	f32 getScore();

	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);
	virtual void onCollision(Component* body1, Component* body2);

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

	f32 m_current_cam_distance = 0.0f;
	f32 m_cam_distance = 18.0f;

	MeshComponent* m_spaceshipMesh = nullptr;
	CameraComponent* m_camera = nullptr;
	Entity* m_cameraEntity = nullptr;

	PlayerControllerComponent* m_player = nullptr;

	f32 m_elapsedSecondsProjectile = 0.5f;


	f32 m_health = 50.0f;
	f32 m_ammo = 50.0f;

	f32 m_score = 0.0f;

};

