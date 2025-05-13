#include "StaticCubeItem.h"

StaticCubeItem::StaticCubeItem()
{
}
StaticCubeItem::~StaticCubeItem()
{
}

void StaticCubeItem::onCreate()
{
	GameItem::onCreate();
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/box.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	mat->addTexture(tex);
	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);
	getTransform()->setScale(Vector3D(10, 10, 10));
	setDirection(Vector3D(0, 0, 0));
	m_collider = createComponent<SphereColliderComponent>();
	m_collider->setRadius(10.0f);
}

void StaticCubeItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
}

void StaticCubeItem::onCollision(Component* body1, Component* body2)
{
	GameItem::onCollision(body1, body2);
}

void StaticCubeItem::onCollisionEnter(Component* body1, Component* body2)
{
	GameItem::onCollisionEnter(body1, body2);
	//if (dynamic_cast<SphereItem*>(body2->getEntity()))
	//{
	//	setDirection(Vector3D(0, 0, 0));
	//}
}