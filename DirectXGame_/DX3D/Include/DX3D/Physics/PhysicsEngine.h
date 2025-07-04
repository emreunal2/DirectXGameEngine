

#pragma once
#include <DX3D/Prerequisites.h>
#include <set>


class PhysicsEngine
{
public:
	explicit PhysicsEngine(Game* game);
	virtual ~PhysicsEngine();
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(const PhysicsEngine&) = delete;
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

	PlayerControllerComponent* m_player = nullptr;
};

