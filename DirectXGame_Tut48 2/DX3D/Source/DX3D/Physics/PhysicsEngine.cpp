#include <DX3D/Physics/PhysicsEngine.h>
#include <DX3D/Entity/TerrainComponent.h>
#include <DX3D/Entity/PlayerControllerComponent.h>
#include <DX3D/Entity/SphereColliderComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Entity/TransformComponent.h>



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

void PhysicsEngine::_processTerrainPlayerCollision(TerrainComponent* terrain, PlayerControllerComponent* player)
{
	if (player == nullptr) return;

	auto playerEntity = player->getEntity();
	
	Vector3D finalPos;

	if (terrain->intersect(playerEntity->getTransform()->getPosition(), player->getMoveDirection(),
		player->getMoveDistance(), player->getHeight(), finalPos))
	{
		playerEntity->getTransform()->setPosition(finalPos);
		playerEntity->onCollision(player, terrain);
		terrain->getEntity()->onCollision(terrain, player);
	}
}


void PhysicsEngine::_processSpherePlayerCollision(SphereColliderComponent* sphere, PlayerControllerComponent* player)
{
	auto playerEntity = player->getEntity();

	Vector3D finalPos;

	auto distVec = playerEntity->getTransform()->getPosition() - sphere->getEntity()->getTransform()->getPosition();
	auto dist = Vector3D::length(distVec);

	if (dist< player->getHeight()+sphere->getRadius())
	{
		playerEntity->onCollision(player, sphere);
		sphere->getEntity()->onCollision(sphere, player);
	}
}

void PhysicsEngine::_processSphereSphereCollision(SphereColliderComponent* sphere1, SphereColliderComponent* sphere2)
{
	auto playerEntity = sphere1->getEntity();

	Vector3D finalPos;

	auto distVec = sphere1->getEntity()->getTransform()->getPosition() - sphere2->getEntity()->getTransform()->getPosition();
	auto dist = Vector3D::length(distVec);
	float sumRadius = sphere1->getRadius() + sphere2->getRadius();

	bool isColliding = dist < sumRadius;
	bool wasColliding = m_collisionPairs.find({ sphere1, sphere2 }) != m_collisionPairs.end();

	if (isColliding && !wasColliding)
	{
		sphere1->getEntity()->onCollisionEnter(sphere1, sphere2);
		sphere2->getEntity()->onCollisionEnter(sphere2, sphere1);
		m_collisionPairs.insert({ sphere1, sphere2 });
		//debug which objects collided
		std::cout << "Collision Enter: " << sphere1->getEntity();
	}
	else if (!isColliding && wasColliding)
	{
		sphere1->getEntity()->onCollisionExit(sphere1, sphere2);
		sphere2->getEntity()->onCollisionExit(sphere2, sphere1);
		m_collisionPairs.erase({ sphere1, sphere2 });
		std::cout << "Collision Exit: " << m_collisionPairs.size() << std::endl;
	}
	else if (isColliding && wasColliding)
	{
		sphere1->getEntity()->onCollisionStay(sphere1, sphere2);
		sphere2->getEntity()->onCollisionStay(sphere2, sphere1);
	}
}

//void PhysicsEngine::_processTerrainSphereCollision(TerrainComponent* terrain, SphereColliderComponent* sphere)
//{
//	auto playerEntity = sphere->getEntity();
//
//	Vector3D finalPos;
//
//	if (terrain->intersect(playerEntity->getTransform()->getPosition(), player->getMoveDirection(),
//		player->getMoveDistance(), sphere->getRadius(), finalPos))
//	{
//		playerEntity->onCollision(player, terrain);
//		terrain->getEntity()->onCollision(terrain, player);
//	}
//}
