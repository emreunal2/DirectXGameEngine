#include "LookDirectionCircle.h"

LookDirectionCircle::LookDirectionCircle() = default;


LookDirectionCircle::~LookDirectionCircle() = default;

void LookDirectionCircle::onCreate()
{
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/box.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Projectile.hlsl");
	mat->addTexture(tex);
	m_circleMesh = this->createComponent<MeshComponent>();
	m_circleMesh->setMesh(mesh);
	m_circleMesh->addMaterial(mat);
}

void LookDirectionCircle::onUpdate(f32 deltaTime)
{
}
