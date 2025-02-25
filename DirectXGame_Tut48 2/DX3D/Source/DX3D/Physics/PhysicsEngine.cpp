/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

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
	for (auto c : m_components)
	{
		if (c == m_player) continue;

		if (auto cc = dynamic_cast<TerrainComponent*>(c))
		{
			_processTerrainPlayerCollision(cc, m_player);
		}
		else if (auto cc = dynamic_cast<SphereColliderComponent*>(c))
		{
			_processSpherePlayerCollision(cc, m_player);
		}


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
}

void PhysicsEngine::removeComponent(Component* component)
{
	m_components.erase(component);
	if (auto c = dynamic_cast<PlayerControllerComponent*>(component))
	{
		m_player = nullptr;
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

	if (dist < sphere1->getRadius() + sphere2->getRadius())
	{
		playerEntity->onCollision(sphere1, sphere2);
		sphere2->getEntity()->onCollision(sphere2, sphere1);
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
