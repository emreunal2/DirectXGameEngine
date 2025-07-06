#include <DX3D/Physics/PhysicsEngine.h>
#include <DX3D/Entity/TerrainComponent.h>
#include <DX3D/Entity/PlayerControllerComponent.h>
#include <DX3D/Entity/SphereColliderComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Entity/TransformComponent.h>
#include <DX3D/Entity/CubeColliderComponent.h>



PhysicsEngine::PhysicsEngine(Game* game):m_game(game)
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::update()
{
	// OLD VERSION ?
	//for (auto c : m_components)
	//{
		//if (c == m_player) continue;

		//if (auto cc = dynamic_cast<TerrainComponent*>(c))
		//{
			//_processTerrainPlayerCollision(cc, m_player);
		//}
		//else if (auto cc = dynamic_cast<SphereColliderComponent*>(c))
		//{
			//TODO: FIX THIS LATER 
			//_processSpherePlayerCollision(cc, m_player);
		//}


		//for (auto c1 : m_components)
		//{
		//	if (c == c1) continue;
		//	if (auto cc = dynamic_cast<TerrainComponent*>(c))
		//	{
		//		if (auto cc1 = dynamic_cast<PlayerControllerComponent*>(c1)) _processTerrainPlayerCollision(cc, cc1);
		//		//if (auto cc1 = dynamic_cast<SphereColliderComponent*>(c1)) _processTerrainSphereCollision(cc1, cc);
		//	}
		//	else if (auto cc = dynamic_cast<PlayerControllerComponent*>(c))
		//	{
		//		if (auto cc1 = dynamic_cast<TerrainComponent*>(c1)) _processTerrainPlayerCollision(cc1, cc);
		//		if (auto cc1 = dynamic_cast<SphereColliderComponent*>(c1)) _processSpherePlayerCollision(cc1, cc);
		//	}
		//	else if (auto cc = dynamic_cast<SphereColliderComponent*>(c))
		//	{
		//		if (auto cc1 = dynamic_cast<PlayerControllerComponent*>(c1)) _processSpherePlayerCollision(cc, cc1);
		//		if (auto cc1 = dynamic_cast<SphereColliderComponent*>(c1)) _processSphereSphereCollision(cc, cc1);
		//	}
		//}
	//}

	// NEW VERSION
	
	for (auto c1 : m_components)
	{
		if (auto sc1 = dynamic_cast<SphereColliderComponent*>(c1))
		{
			for (auto c2 : m_components)
			{
				if (c1 == c2) continue;
				if (auto sc2 = dynamic_cast<SphereColliderComponent*>(c2))
				{
					_processSphereSphereCollision(sc1, sc2);
				}
				else if (auto cc = dynamic_cast<CubeColliderComponent*>(c2))
				{
					_processSphereCubeCollision(sc1, cc);
				}
			}
		}
	}
	
}

void PhysicsEngine::addComponent(Component* component)
{
	if (auto c = dynamic_cast<TerrainComponent*>(component))
		m_components.emplace(c);
	else if (auto c = dynamic_cast<PlayerControllerComponent*>(component))
	{
		m_components.emplace(c);
		m_player = c;
	}
	else if (auto c = dynamic_cast<SphereColliderComponent*>(component))
		m_components.emplace(c);
	else if (auto c = dynamic_cast<CubeColliderComponent*>(component))
		m_components.emplace(c);
	else
	{
		std::cout << "Unknown component type added to PhysicsEngine: " << typeid(*component).name() << std::endl;
		return;
	}
	std::cout << "Number of Components: " << m_components.size() << std::endl;
}

void PhysicsEngine::removeComponent(Component* component)
{
	m_components.erase(component);
	if (auto c = dynamic_cast<PlayerControllerComponent*>(component))
	{
		m_player = nullptr;
	}
	for (auto it = m_collisionPairs.begin(); it != m_collisionPairs.end(); )
	{
		if (it->a == component || it->b == component)
			it = m_collisionPairs.erase(it);
		else
			++it;
	}
}

int PhysicsEngine::getNumberOfComponents()
{
	return m_components.size();
}

void PhysicsEngine::_processSphereSphereCollision(SphereColliderComponent* sphere1, SphereColliderComponent* sphere2)
{
	auto pos1 = sphere1->getEntity()->getTransform()->getPosition();
	auto pos2 = sphere2->getEntity()->getTransform()->getPosition();

	// Get the lengths and radii
	float length1 = sphere1->getLength();
	float length2 = sphere2->getLength();
	float radius1 = sphere1->getRadius();
	float radius2 = sphere2->getRadius();

	// Calculate start and end points of each capsule
	Vector3D start1 = pos1 - Vector3D(0, length1 / 2.0f, 0);
	Vector3D end1 = pos1 + Vector3D(0, length1 / 2.0f, 0);

	Vector3D start2 = pos2 - Vector3D(0, length2 / 2.0f, 0);
	Vector3D end2 = pos2 + Vector3D(0, length2 / 2.0f, 0);

	// Calculate segment vectors
	Vector3D d1 = end1 - start1;
	Vector3D d2 = end2 - start2;
	Vector3D r = start1 - start2;

	// Length squared of each segment
	float d1LengthSq = (d1.x * d1.x) + (d1.y * d1.y) + (d1.z * d1.z);
	float d2LengthSq = (d2.x * d2.x) + (d2.y * d2.y) + (d2.z * d2.z);

	// Dot products
	float d1_r = (d1.x * r.x) + (d1.y * r.y) + (d1.z * r.z);
	float d2_r = (d2.x * r.x) + (d2.y * r.y) + (d2.z * r.z);
	float d1_d2 = (d1.x * d2.x) + (d1.y * d2.y) + (d1.z * d2.z);

	// Determinant
	float denom = (d1LengthSq * d2LengthSq) - (d1_d2 * d1_d2);

	// Clamping parameters
	float s = 0.0f, t = 0.0f;

	if (denom != 0.0f)
	{
		s = ((d1_d2 * d2_r) - (d2LengthSq * d1_r)) / denom;
		s = (s < 0.0f) ? 0.0f : (s > 1.0f ? 1.0f : s);
	}

	// Recalculate t with the new s
	float tDenom = d2LengthSq - (d1_d2 * s);

	if (tDenom != 0.0f)
	{
		t = (d2_r + (d1_d2 * s)) / tDenom;
		t = (t < 0.0f) ? 0.0f : (t > 1.0f ? 1.0f : t);
	}

	// Closest points on each segment
	Vector3D closestPoint1 = Vector3D(
		start1.x + d1.x * s,
		start1.y + d1.y * s,
		start1.z + d1.z * s
	);

	Vector3D closestPoint2 = Vector3D(
		start2.x + d2.x * t,
		start2.y + d2.y * t,
		start2.z + d2.z * t
	);

	// Distance between closest points
	float distVecX = closestPoint1.x - closestPoint2.x;
	float distVecY = closestPoint1.y - closestPoint2.y;
	float distVecZ = closestPoint1.z - closestPoint2.z;

	float distSq = (distVecX * distVecX) + (distVecY * distVecY) + (distVecZ * distVecZ);
	float dist = sqrt(distSq);

	// Calculate the sum of the radii
	float sumRadius = radius1 + radius2;

	// Collision check
	bool isColliding = dist < sumRadius;
	bool wasColliding = (m_collisionPairs.find({ sphere1, sphere2 }) != m_collisionPairs.end() || m_collisionPairs.find({ sphere2, sphere1 }) != m_collisionPairs.end());


	if (isColliding && !wasColliding)
	{
		sphere1->getEntity()->onCollisionEnter(sphere1, sphere2);
		//sphere2->getEntity()->onCollisionEnter(sphere2, sphere1);
		m_collisionPairs.insert({ sphere1, sphere2 });
		//debug which objects collided
		//std::cout << "Collision Enter: " << sphere1->getEntity() << "and " << sphere2->getEntity() << std::endl;
		
	}
	else if (!isColliding && wasColliding)
	{
		sphere1->getEntity()->onCollisionExit(sphere1, sphere2);
		sphere2->getEntity()->onCollisionExit(sphere2, sphere1);
		m_collisionPairs.erase({ sphere1, sphere2 });
		//std::cout << "Collision Exit: " << m_collisionPairs.size() << std::endl;
	}
	else if (isColliding && wasColliding)
	{
		sphere1->getEntity()->onCollisionStay(sphere1, sphere2);
		sphere2->getEntity()->onCollisionStay(sphere2, sphere1);
	}
}

void PhysicsEngine::_processSphereCubeCollision(SphereColliderComponent* sphere, CubeColliderComponent* cube)
{
	auto sphereEntity = sphere->getEntity();
	auto cubeEntity = cube->getEntity();

	Vector3D sphereCenter = sphereEntity->getTransform()->getPosition();
	float sphereRadius = sphere->getRadius();

	Vector3D cubeCenter = cubeEntity->getTransform()->getPosition();
	Vector3D cubeExtent = cube->getExtents(); // Half sizes (x, y, z)

	// Find closest point on the cube to the sphere center
	float closestX = std::max(cubeCenter.x - cubeExtent.x, std::min(sphereCenter.x, cubeCenter.x + cubeExtent.x));
	float closestY = std::max(cubeCenter.y - cubeExtent.y, std::min(sphereCenter.y, cubeCenter.y + cubeExtent.y));
	float closestZ = std::max(cubeCenter.z - cubeExtent.z, std::min(sphereCenter.z, cubeCenter.z + cubeExtent.z));

	Vector3D closestPoint(closestX, closestY, closestZ);

	// Distance vector from sphere to closest point
	Vector3D delta = sphereCenter - closestPoint;
	float distSquared = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;

	bool isColliding = distSquared < (sphereRadius * sphereRadius);
	bool wasColliding = m_collisionPairs.find({ sphere, cube }) != m_collisionPairs.end();

	if (isColliding && !wasColliding)
	{
		// Basic bounce-back response
		Vector3D normal = Vector3D::normalize(delta);
		Vector3D oldPos = sphereEntity->getTransform()->getPosition();
		Vector3D newPos = closestPoint + normal * sphereRadius;
		sphereEntity->getTransform()->setPosition(newPos);

		// Invert direction (elastic bounce, crude for now)

		sphereEntity->onCollisionEnter(sphere, cube);
		m_collisionPairs.insert({ sphere, cube });
	}
	else if (!isColliding && wasColliding)
	{
		sphereEntity->onCollisionExit(sphere, cube);
		m_collisionPairs.erase({ sphere, cube });
	}
	else if (isColliding && wasColliding)
	{
		sphereEntity->onCollisionStay(sphere, cube);
	}
}

