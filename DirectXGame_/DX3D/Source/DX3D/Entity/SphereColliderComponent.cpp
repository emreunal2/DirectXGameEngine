

#include <DX3D/Entity/SphereColliderComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Physics/PhysicsEngine.h>


SphereColliderComponent::SphereColliderComponent() = default;

SphereColliderComponent::~SphereColliderComponent()
{
	try {
		m_entity->getWorld()->getGame()->getPhysicsEngine()->removeComponent(this);
	}
	catch (...) {
	}
}

void SphereColliderComponent::setRadius(f32 radius)
{
	m_radius = radius;
}

f32 SphereColliderComponent::getRadius()
{
	return m_radius;
}


void SphereColliderComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getPhysicsEngine()->addComponent(this);
}
