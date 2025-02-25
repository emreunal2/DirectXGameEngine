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

#include "Spaceship.h"
#include "BoxItem.h"
#include "InfoItem.h"
#include "AsteroidItem.h"



Spaceship::Spaceship()
{
}

Spaceship::~Spaceship()
{
}

f32 Spaceship::getScore()
{
	return m_score;
}

void Spaceship::onCreate()
{
	//Load all the assets
	auto tex =   getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/spaceship.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	mat->addTexture(tex);

	m_spaceshipMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_spaceshipMesh->setMesh(mesh);
	m_spaceshipMesh->addMaterial(mat);

	//Create the camera that follows the spaceship
	m_cameraEntity = getWorld()->createEntity<Entity>();
	m_camera = m_cameraEntity->createComponent<CameraComponent>();
	m_camera->setFarPlane(40000.0f);

	m_player = createComponent<PlayerControllerComponent>();

	getTransform()->setPosition(Vector3D(0, 100, 0));	
	getTransform()->setScale(Vector3D(0.5, 0.5, 0.5));
}

void Spaceship::onUpdate(f32 deltaTime)
{
	auto scale = 0.5f;

	auto input = getInputSystem();

	f32 m_forward = 0.0f;
	f32 rightward = 0.0f;

	f32 speed = 1.0f;
	bool turbo = false;

	//Spaceship controls
	if (input->isKeyDown(Key::W))
	{
		m_forward = 1.0f;
	}
	if (input->isKeyDown(Key::S))
	{
		m_forward = -1.0f;
	}
	if (input->isKeyDown(Key::A))
	{
		rightward = -1.0f;
	}
	if (input->isKeyDown(Key::D))
	{
		rightward = 1.0f;
	}
	if (input->isKeyDown(Key::Shift))
	{
		speed = 1.2f;
		turbo = true;
	}





	//Handle position and rotation of spaceship and camera
	//With smooth movements, thanks to the lerp function

	if (m_forward)
	{
		if (turbo)
		{
			if (m_forward > 0.0f) m_cam_distance = 25.0f* scale;
			else m_cam_distance = 5.0f * scale;
		}
		else
		{
			if (m_forward > 0.0f) m_cam_distance = 20.0f * scale;
			else m_cam_distance = 9.0f * scale;
		}
	}
	else
	{
		m_cam_distance = 18.0f * scale;
	}

	auto vec = Vector3D::lerp(Vector3D(m_current_cam_distance, 0, 0),
		Vector3D(m_cam_distance, 0, 0), 2.0f * deltaTime);
	m_current_cam_distance = vec.x;

	auto deltapos = input->getDeltaMousePosition();
	m_yaw += deltapos.x * 0.001f;
	m_pitch += deltapos.y * 0.001f;

	if (m_pitch < -1.57f)
		m_pitch = -1.57f;
	else if (m_pitch > 1.57f)
		m_pitch = 1.57f;


	auto curr = Vector3D::lerp(Vector3D(m_oldPitch, m_oldYaw, 0), Vector3D(m_pitch, m_yaw, 0), 5.0f * deltaTime);
	m_oldPitch = curr.x;
	m_oldYaw = curr.y;

	getTransform()->setRotation(Vector3D(m_oldPitch, m_oldYaw, 0));

	auto curr_cam = Vector3D::lerp(Vector3D(m_camPitch, m_camYaw, 0), Vector3D(m_pitch, m_yaw, 0), 3.0f * deltaTime);
	m_camPitch = curr_cam.x;
	m_camYaw = curr_cam.y;

	m_cameraEntity->getTransform()->setRotation(Vector3D(m_camPitch, m_camYaw, 0));


	Matrix4x4 w;
	getTransform()->getWorldMatrix(w);
	auto zdir = w.getZDirection();
	auto xdir = w.getXDirection();
	auto ydir = w.getYDirection();


	auto pos = getTransform()->getPosition() + zdir * m_forward * deltaTime * 100.0f * speed;

	if (pos.x > 700) pos.x = 700;
	if (pos.z > 700) pos.z = 700;
	if (pos.x < -200) pos.x = -200;
	if (pos.z < -200) pos.z = -200;
	if (pos.y < 15) pos.y = 15;

	getTransform()->setPosition(pos);


	Matrix4x4 w2;
	m_cameraEntity->getTransform()->getWorldMatrix(w2);
	zdir = w2.getZDirection();
	xdir = w2.getXDirection();
	ydir = w2.getYDirection();


	auto camPos = Vector3D(pos + zdir * -m_current_cam_distance);
	camPos = camPos + ydir * 6.5f * scale;

	m_cameraEntity->getTransform()->setPosition(camPos);

	m_player->move(zdir* m_forward, deltaTime);	
	
	m_elapsedSecondsProjectile += deltaTime;
	
}

void Spaceship::onCollision(Component* body1, Component* body2)
{
	if (dynamic_cast<TerrainComponent*>(body2))
	{
		Matrix4x4 w;
		getTransform()->getWorldMatrix(w);
		auto zdir = w.getZDirection();
		auto pos = getTransform()->getPosition();

		if (pos.x > -50 && pos.x < 500 && pos.z > -50 && pos.z < 500)
		{
			pos.y+= 100.0f;
			getTransform()->setPosition(pos);

			m_yaw = 0;
			m_pitch = 1.57f;
			m_camYaw = 0;
			m_camPitch = 0;
		}

		m_score -= 1.0f;

		auto info = getWorld()->createEntity<InfoItem>();
		info->setText(L"- 1 box");
	}

	if (dynamic_cast<BoxItem*>(body2->getEntity()))
	{
		m_score += 1.0f;
		body2->getEntity()->release();
		auto info = getWorld()->createEntity<InfoItem>();
		info->setText(L"+ 1 box");
	}

	if (dynamic_cast<AsteroidItem*>(body2->getEntity()))
	{
		m_score -= 1.0f;
		body2->getEntity()->release();
		auto info = getWorld()->createEntity<InfoItem>();
		info->setText(L"- 1 box");
	}

}
