#include "StaticSphereItem.h"

StaticSphereItem::StaticSphereItem()
{
}
StaticSphereItem::~StaticSphereItem()
{
}

void StaticSphereItem::onCreate()
{
	GameItem::onCreate();
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
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
	m_collider->setRadius(1.0f);
	//m_collider->setStatic(true);
}

void StaticSphereItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
}

void StaticSphereItem::onCollision(Component* body1, Component* body2)
{
	GameItem::onCollision(body1, body2);
}

