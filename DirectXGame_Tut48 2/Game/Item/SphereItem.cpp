#include "SphereItem.h"
SphereItem::SphereItem()
{
}
SphereItem::~SphereItem()
{
}


void SphereItem::onCreate()
{
	GameItem::onCreate();
	//Load all the assets
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
	//Add the texture to material
	mat->addTexture(tex);
	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);
	getTransform()->setScale(Vector3D(20, 20, 20));
	m_collider->setRadius(5.0f);
}

void SphereItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
	ApplyMovement(deltaTime);
}

void SphereItem::onCollision(Component* body1, Component* body2)
{
}

void SphereItem::ApplyMovement(f32 deltaTime)
{
	auto pos = getTransform()->getPosition();
	// move left
	m_direction = Vector3D(0, 0, 0);
	ApplyGravity();
	pos = pos + m_direction * deltaTime;
	getTransform()->setPosition(pos);
}

// TODO GRAVITY SYSTEM MAY CAUSE PROBLEMS BECAUSE ITS NOT IN THE PHYSICS ENGINE AND
// I USE GET GAME FOR EVERY ENTITY AT EVERY FRAME SO FIX IT 
void SphereItem::ApplyGravity()
{
	//Apply to direction not position
	auto gravityValue = getWorld()->getGame()->getGravity();
	m_direction.y -= gravityValue;

}