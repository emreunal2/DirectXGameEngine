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
	m_elasticity = 1.0f;
	//set color
	m_itemMesh->removeMaterial(0);
	auto mat2 = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
	mat2->addTexture(tex);
	m_itemMesh->addMaterial(mat2);

	float radius = m_collider->getRadius();
	m_inertia = 0.4f * m_mass * radius * radius;

}

void SphereItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
	ApplyGravity(deltaTime);
	ApplyMovement(deltaTime);
	ApplyRotation(deltaTime);
	std::cout << "Rotation Debug: " << getTransform()->getRotation().x << " " << getTransform()->getRotation().y << " " << getTransform()->getRotation().z << std::endl;
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
		//std::cout << "Speed before collision: " << " obj1 x: " << v1.x <<" obj1 y: " << v1.y << " obj1 z: " << v1.z << " and " << " obj2 x: " << v2.x << " obj2 y: " << v2.y << " obj2 z: " << v2.z << std::endl;

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

		Vector3D pThis = getTransform()->getPosition();
		Vector3D pOther = otherSphere->getTransform()->getPosition();

		// ==== Precompute shared values ====
		Vector3D p1 = getTransform()->getPosition();
		Vector3D p2 = otherSphere->getTransform()->getPosition();

		Vector3D contact;
		contact.x = (p1.x + p2.x) * 0.5f;
		contact.y = (p1.y + p2.y) * 0.5f;
		contact.z = (p1.z + p2.z) * 0.5f;

		// r vectors
		Vector3D r1, r2;
		r1.x = contact.x - p1.x;
		r1.y = contact.y - p1.y;
		r1.z = contact.z - p1.z;

		r2.x = contact.x - p2.x;
		r2.y = contact.y - p2.y;
		r2.z = contact.z - p2.z;

		// impulse vectors
		Vector3D impulse1, impulse2;
		impulse1.x = newVelocity1.x - v1.x;
		impulse1.y = newVelocity1.y - v1.y;
		impulse1.z = newVelocity1.z - v1.z;

		impulse2.x = newVelocity2.x - v2.x;
		impulse2.y = newVelocity2.y - v2.y;
		impulse2.z = newVelocity2.z - v2.z;

		// torques
		Vector3D torque1, torque2;
		torque1.x = r1.y * impulse1.z - r1.z * impulse1.y;
		torque1.y = r1.z * impulse1.x - r1.x * impulse1.z;
		torque1.z = r1.x * impulse1.y - r1.y * impulse1.x;

		torque2.x = r2.y * impulse2.z - r2.z * impulse2.y;
		torque2.y = r2.z * impulse2.x - r2.x * impulse2.z;
		torque2.z = r2.x * impulse2.y - r2.y * impulse2.x;

		// inertia
		float radius1 = m_collider->getRadius();
		float inertia1 = 0.4f * m_mass * radius1 * radius1;

		float radius2 = otherSphere->m_collider->getRadius();
		float mass2 = otherSphere->getMass();
		float inertia2 = 0.4f * mass2 * radius2 * radius2;

		// angular accelerations
		Vector3D angAccel1, angAccel2;
		angAccel1.x = torque1.x / inertia1;
		angAccel1.y = torque1.y / inertia1;
		angAccel1.z = torque1.z / inertia1;

		angAccel2.x = torque2.x / inertia2;
		angAccel2.y = torque2.y / inertia2;
		angAccel2.z = torque2.z / inertia2;

		// ==== Now apply both angular updates ====
		m_angularVelocity.x += angAccel1.x;
		m_angularVelocity.y += angAccel1.y;
		m_angularVelocity.z += angAccel1.z;

		otherSphere->m_angularVelocity.x += angAccel2.x;
		otherSphere->m_angularVelocity.y += angAccel2.y;
		otherSphere->m_angularVelocity.z += angAccel2.z;

		//std::cout << "Speed after collision: " << this->getDirection().x << " and " << otherSphere->getDirection().x << std::endl;
	}
	if (dynamic_cast<StaticSphereItem*>(body2->getEntity()))
	{
		setDirection(Vector3D(0, 0, 0));
	}
	if (dynamic_cast<StaticCubeItem*>(body2->getEntity()))
	{
		Vector3D v = getDirection();
		Vector3D n = body2->getEntity()->getTransform()->getPosition() - getTransform()->getPosition();
		n = Vector3D::normalize(n);
		float e = m_elasticity;

		float dot = v.x * n.x + v.y * n.y + v.z * n.z;

		float newX = v.x - (1 + e) * dot * n.x;
		float newY = v.y - (1 + e) * dot * n.y;
		float newZ = v.z - (1 + e) * dot * n.z;

		setDirection(Vector3D(newX, newY, newZ));
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

void SphereItem::ApplyRotation(f32 deltaTime)
{
	Vector3D rot = getTransform()->getRotation();
	rot = rot + m_angularVelocity * deltaTime;

	rot.x = fmodf(rot.x, 6.2831f);
	rot.y = fmodf(rot.y, 6.2831f);
	rot.z = fmodf(rot.z, 6.2831f);

	getTransform()->setRotation(rot);

	// Damping to simulate friction
	float damping = 0.98f;
	m_angularVelocity = m_angularVelocity * damping;
}

f32 SphereItem::getMass()
{
	return m_mass;
}
void SphereItem::setMass(f32 mass)
{
	m_mass = mass;
	float radius = m_collider->getRadius();
	m_inertia = 0.4 * m_mass * radius * radius;
}
f32 SphereItem::getElasticity()
{
	return m_elasticity;
}
void SphereItem::setElasticity(f32 elasticity)
{
	m_elasticity = elasticity;
}

void SphereItem::setMaterialType(MaterialType type)
{
	m_materialType = type;
	if (m_materialType == MaterialType::DEFAULT)
	{
		setElasticity(1.0f);
		auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
		auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
		mat->addTexture(tex);
		m_itemMesh->removeMaterial(0);
		m_itemMesh->addMaterial(mat);
	}
	else if (m_materialType == MaterialType::GRASS)
	{
		setElasticity(0.5f);
		auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
		auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
		mat->addTexture(tex);
		m_itemMesh->removeMaterial(0);
		m_itemMesh->addMaterial(mat);
	}
	else if (m_materialType == MaterialType::METAL)
	{
		setElasticity(0.0f);
		auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/asteroid.jpg");
		auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/Base.hlsl");
		mat->addTexture(tex);
		m_itemMesh->removeMaterial(0);
		m_itemMesh->addMaterial(mat);
	}
}
