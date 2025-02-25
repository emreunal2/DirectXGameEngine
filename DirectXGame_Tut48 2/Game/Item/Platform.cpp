#include "Platform.h"

Platform::Platform()
{
}

Platform::~Platform()
{
}

void Platform::onCreate()
{
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	mat->addTexture(tex);

	m_platformMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_platformMesh->setMesh(mesh);
	m_platformMesh->addMaterial(mat);
}

void Platform::onUpdate(f32 deltaTime)
{
}