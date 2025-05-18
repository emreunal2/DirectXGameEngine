#include "SphereItem.h"
#include "StaticSphereItem.h"
#include "StaticCubeItem.h"
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
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
	//Add the texture to material
	mat->addTexture(tex);
	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);
	getTransform()->setScale(Vector3D(1, 1, 1));
	//setDirection(Vector3D(0, 0, 0));
	m_collider = createComponent<SphereColliderComponent>();
	m_collider->setRadius(1.0f);
	m_mass = 1.0f;

}

void SphereItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
	ApplyGravity(deltaTime);
	ApplyMovement(deltaTime);
}

void SphereItem::onCollision(Component* body1, Component* body2)
{

}
void SphereItem::onCollisionEnter(Component* body1, Component* body2)
{

	if (dynamic_cast<SphereItem*>(body2->getEntity()))
	{
		auto otherSphere = dynamic_cast<SphereItem*>(body2->getEntity());
		float m1 = m_mass;
		float m2 = otherSphere->getMass();

		float e1 = m_elasticity;
		float e2 = otherSphere->getElasticity();
		float e = (e1 + e2) / 2;
		Vector3D v1 = getDirection();
		Vector3D v2 = otherSphere->getDirection();
		std::cout << "Speed before collision: " << " obj1 x: " << v1.x <<" obj1 y: " << v1.y << " obj1 z: " << v1.z << " and " << " obj2 x: " << v2.x << " obj2 y: " << v2.y << " obj2 z: " << v2.z << std::endl;

		float newVelocity1X = ((v1.x * (m1 - e * m2)) + (v2.x * (1 + e) * m2)) / (m1 + m2);
		float newVelocity2X = ((v2.x * (m2 - e * m1)) + (v1.x * (1 + e) * m1)) / (m1 + m2);

		float newVelocity1Y = ((v1.y * (m1 - e * m2)) + (v2.y * (1 + e) * m2)) / (m1 + m2);
		float newVelocity2Y = ((v2.y * (m2 - e * m1)) + (v1.y * (1 + e) * m1)) / (m1 + m2);


		float newVelocity1Z = ((v1.z * (m1 - e * m2)) + (v2.z * (1 + e) * m2)) / (m1 + m2);
		float newVelocity2Z = ((v2.z * (m2 - e * m1)) + (v1.z * (1 + e) * m1)) / (m1 + m2);

		Vector3D newVelocity1(newVelocity1X, newVelocity1Y, newVelocity1Z);
		Vector3D newVelocity2(newVelocity2X, newVelocity2Y, newVelocity2Z);

		setDirection(newVelocity1);
		otherSphere->setDirection(newVelocity2);
		setDirection(newVelocity1);
		otherSphere->setDirection(newVelocity2);
		std::cout << "Speed after collision: " << this->getDirection().x << " and " << otherSphere->getDirection().x << std::endl;
	}
	if (dynamic_cast<StaticSphereItem*>(body2->getEntity()))
	{
		setDirection(Vector3D(0, 0, 0));
	}
	if (dynamic_cast<StaticCubeItem*>(body2->getEntity()))
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

f32 SphereItem::getMass()
{
	return m_mass;
}
void SphereItem::setMass(f32 mass)
{
	m_mass = mass;
}
f32 SphereItem::getElasticity()
{
	return m_elasticity;
}
void SphereItem::setElasticity(f32 elasticity)
{
	m_elasticity = elasticity;
}
