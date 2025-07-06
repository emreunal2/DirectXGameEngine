#include <DX3D/Entity/CubeColliderComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Physics/PhysicsEngine.h>

CubeColliderComponent::CubeColliderComponent()
{
}

CubeColliderComponent::~CubeColliderComponent()
{
	m_entity->getWorld()->getGame()->getPhysicsEngine()->removeComponent(this);
}
void CubeColliderComponent::setExtents(const Vector3D& extents)
{
	m_extents = extents;
}
Vector3D CubeColliderComponent::getExtents() const
{
	return m_extents;
}
void CubeColliderComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getPhysicsEngine()->addComponent(this);
}
