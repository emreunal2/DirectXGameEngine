

#include "AsteroidItem.h"
#include "../MainGame.h"


AsteroidItem::AsteroidItem() = default;

AsteroidItem::~AsteroidItem() = default;

void AsteroidItem::setAPosition(const Vector3D& position)
{
	m_pos = position;
	getTransform()->setPosition(position);
}

void AsteroidItem::setADirection(const Vector3D& direction)
{
	m_direction = Vector3D::normalize(direction);
}


void AsteroidItem::onCreate()
{
	Entity::onCreate();

	//Load all the assets
	auto astroTex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/asteroid.jpg");
	auto astroMesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/asteroid.obj");
	auto astroMat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	astroMat->addTexture(astroTex);

	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(astroMesh);
	m_itemMesh->addMaterial(astroMat);	

	m_collider = createComponent<SphereColliderComponent>();
	m_collider->setRadius(10.0f);

	getTransform()->setScale(Vector3D(2, 2, 2));
}

void AsteroidItem::onUpdate(f32 deltaTime)
{
	Entity::onUpdate(deltaTime);

	m_elapsedSecondsLastUpdate += deltaTime;

	auto pos = getTransform()->getPosition();

	pos = pos + m_direction * m_speed * deltaTime;
	getTransform()->setPosition(pos);

	if (pos.gety() < -100.0f)
	{
		this->release();
	}
}

void AsteroidItem::onCollision(Component* body1, Component* body2)
{
}
