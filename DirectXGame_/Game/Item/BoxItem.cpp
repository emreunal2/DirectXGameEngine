

#include "BoxItem.h"

BoxItem::BoxItem() = default;

BoxItem::~BoxItem() = default;

void BoxItem::onCreate()
{
	GameItem::onCreate();
	//Load all the assets
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/box.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
	//Add the texture to material
	mat->addTexture(tex);

	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);

	getTransform()->setScale(Vector3D(5, 5, 5));
	m_collider->setRadius(5.0f);
}

void BoxItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;

	m_angle += 3.14f * deltaTime;

	auto pos = m_pos;

	getTransform()->setRotation(Vector3D(0, m_angle * 0.4f, 0));
	getTransform()->setPosition(pos);
}

void BoxItem::onCollision(Component* body1, Component* body2)
{
}

