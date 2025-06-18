

#include "Spaceship.h"
#include "BoxItem.h"
#include "InfoItem.h"
#include "AsteroidItem.h"
#include "LookDirectionCircle.h"


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
	auto tex2 = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/asteroid.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/spaceship.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/ToonShading.hlsl");
	auto mat2 = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/ToonShading.hlsl");
	//Add the texture to material
	mat->addTexture(tex);
	//mat2->addTexture(tex2);
	m_spaceshipMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_spaceshipMesh->setMesh(mesh);
	m_spaceshipMesh->addMaterial(mat);
	//m_spaceshipMesh->addMaterial(mat2);
	//m_spaceshipMesh->removeMaterial(0);
	
	//Create the camera that follows the spaceship
	m_cameraEntity = getWorld()->createEntity<Entity>();
	m_camera = m_cameraEntity->createComponent<CameraComponent>();
	m_camera->setFarPlane(40000.0f);

	m_player = createComponent<PlayerControllerComponent>();

	getTransform()->setPosition(Vector3D(0, 100, 0));	

	m_circleEntity = getWorld()->createEntity<LookDirectionCircle>();
	m_circleEntity->getTransform()->setScale(Vector3D(1.5, 1.5, 1.5));
}

void Spaceship::onUpdate(f32 deltaTime)
{

	auto input = getInputSystem();

	f32 m_forward = 0.0f;
	f32 rightward = 0.0f;

	f32 speed = 1.0f;
	bool turbo = false;
	f32 lookup = 0.0f;
	//Spaceship controls
	if (input->isKeyDown(Key::W))
	{
		lookup = 1.0f;
	}
	if (input->isKeyDown(Key::S))
	{
		lookup = -1.0f;
	}
	if (input->isKeyDown(Key::A))
	{
		rightward = -1.0f;
	}
	if (input->isKeyDown(Key::D))
	{
		rightward = 1.0f;
	}
	if (input->isKeyUp(Key::Space))
	{
		m_jump = true;
	}
	if (input->isKeyDown(Key::LessThan))
	{
		auto info = getWorld()->createEntity<InfoItem>();
		info->setText(L"Time Scale = 0.5");
		getWorld()->getGame()->setTimeScale(0.5f);
	}
	if (input->isKeyDown(Key::GreaterThan))
	{
		auto info = getWorld()->createEntity<InfoItem>();
		info->setText(L"Time Scale = 1");
		getWorld()->getGame()->setTimeScale(1.0f);
	}
	if (input->isKeyDown(Key::Equals))
	{

		m_current_cam_distance -= m_zoomSpeed * deltaTime;
		if (m_current_cam_distance < 20.0f) m_current_cam_distance = 20.0f;
	}
	if (input->isKeyDown(Key::Minus))
	{
		m_current_cam_distance += m_zoomSpeed * deltaTime;
		if (m_current_cam_distance > 200.0f) m_current_cam_distance = 200.0f;
	}

	m_cameraEntity->getTransform()->setRotation(Vector3D(m_camPitch, m_camYaw, 0));


	Matrix4x4 w;
	getTransform()->getWorldMatrix(w);
	auto zdir = w.getZDirection();
	auto xdir = w.getXDirection();
	auto ydir = w.getYDirection();

	auto pos = getTransform()->getPosition() + zdir * m_forward * deltaTime * 100.0f * speed + xdir * rightward * deltaTime * 100.0f * speed;
	if (m_jump)
	{
		pos = pos + ydir * 50.0f * lookup;
		m_jump = false;
	}
	//auto pos = getTransform()->getPosition() + zdir * m_forward * deltaTime * 100.0f * speed;


	getTransform()->setPosition(pos);
	m_circleEntity->getTransform()->setPosition(pos + xdir * 20.0f * rightward + ydir * 20.0f * lookup);

	Matrix4x4 w2;
	m_cameraEntity->getTransform()->getWorldMatrix(w2);
	zdir = w2.getZDirection();
	xdir = w2.getXDirection();
	ydir = w2.getYDirection();


	auto camPos = Vector3D(pos + zdir * -m_current_cam_distance);
	camPos = camPos + ydir * 6.5f;

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
