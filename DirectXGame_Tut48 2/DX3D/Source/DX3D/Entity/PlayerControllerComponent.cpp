

#include <DX3D/Entity/PlayerControllerComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Physics/PhysicsEngine.h>


PlayerControllerComponent::PlayerControllerComponent()
{
}

PlayerControllerComponent::~PlayerControllerComponent()
{
	try {
		m_entity->getWorld()->getGame()->getPhysicsEngine()->removeComponent(this);
	}
	catch (...) {
		// Handle any exceptions that may occur during cleanup
	}
}

void PlayerControllerComponent::setHeight(f32 height)
{
	m_height = height;
}

f32 PlayerControllerComponent::getHeight()
{
	return m_height;
}

Vector3D PlayerControllerComponent::getMoveDirection()
{
	return m_direction;
}

f32 PlayerControllerComponent::getMoveDistance()
{
	return m_distance;
}

void PlayerControllerComponent::move(const Vector3D& direction, f32 distance)
{
	m_distance = distance;
	m_direction = Vector3D::normalize(direction);
}

void PlayerControllerComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getPhysicsEngine()->addComponent(this);
}
