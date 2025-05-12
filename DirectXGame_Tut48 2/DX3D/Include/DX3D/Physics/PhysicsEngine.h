

#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Physics/CollisionPair.h>
#include <set>


class PhysicsEngine
{
public:
	PhysicsEngine(Game* game);
	virtual ~PhysicsEngine();

	void update();
public:
	void addComponent(Component* component);
	void removeComponent(Component* component);
private:
	void _processTerrainPlayerCollision(TerrainComponent* terrain, PlayerControllerComponent* player);
	void _processSpherePlayerCollision(SphereColliderComponent* sphere, PlayerControllerComponent* player);
	void _processSphereSphereCollision(SphereColliderComponent* sphere1, SphereColliderComponent* sphere2);
	void _processTerrainSphereCollision(TerrainComponent* terrain, SphereColliderComponent* sphere);
private:
	Game* m_game = nullptr;

	std::set<Component*> m_components;
	std::set<Component*> m_checkedComponents;
	std::set<CollisionPair> m_collisionPairs;

	PlayerControllerComponent* m_player = nullptr;
};

