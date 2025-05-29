

#include "AsteroidItem.h"
#include "../MainGame.h"


AsteroidItem::AsteroidItem()
{
}

AsteroidItem::~AsteroidItem()
{
}

void AsteroidItem::setPosition(const Vector3D& position)
{
	m_pos = position;
	getTransform()->setPosition(position);
}

void AsteroidItem::setDirection(const Vector3D& direction)
{
	m_direction = Vector3D::normalize(direction);
}

void AsteroidItem::setSpeed(f32 speed)
{
}

void AsteroidItem::onCreate()
{
	Entity::onCreate();

	//Load all the assets
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/asteroid.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/asteroid.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	mat->addTexture(tex);

	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);	

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

	if (pos.y < -100.0f)
	{
		this->release();
	}
}

void AsteroidItem::onCollision(Component* body1, Component* body2)
{
}
