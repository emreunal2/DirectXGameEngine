#include "SphereItem.h"
#include "StaticSphereItem.h"
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
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	mat->addTexture(tex);
	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);
	getTransform()->setScale(Vector3D(20, 20, 20));
	//setDirection(Vector3D(0, 0, 0));
	m_collider->setRadius(5.0f);
}

void SphereItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
	ApplyGravity(deltaTime);
	ApplyMovement(deltaTime);
}

void SphereItem::onCollision(Component* body1, Component* body2)
{

	if (dynamic_cast<SphereItem*>(body2->getEntity()))
	{
		Vector3D v1 = getDirection();
		Vector3D v2 = dynamic_cast<SphereItem*>(body2->getEntity())->getDirection();
		Vector3D newVelocity;
		newVelocity.x = (v1.x +v2.x) + 0.5f;
		newVelocity.y = (v1.y + v2.y) + 0.5f;
		newVelocity.z = (v1.z + v2.z) + 0.5f;
		setDirection(newVelocity);
	}
	if (dynamic_cast<StaticSphereItem*>(body2->getEntity()))
	{
		setDirection(Vector3D(0, 0, 0));

	}
}

void SphereItem::ApplyMovement(f32 deltaTime)
{
	auto pos = getTransform()->getPosition();
	pos = pos + m_direction * deltaTime;
	getTransform()->setPosition(pos);
}

// TODO GRAVITY SYSTEM MAY CAUSE PROBLEMS BECAUSE ITS NOT IN THE PHYSICS ENGINE AND
// I USE GET GAME FOR EVERY ENTITY AT EVERY FRAME SO FIX IT 
void SphereItem::ApplyGravity(f32 deltaTime)
{
	//Apply to direction not position
	auto gravityValue = getWorld()->getGame()->getGravity();
	//auto gravityValue = -9.81f;
	m_direction.y -= gravityValue * deltaTime;

}