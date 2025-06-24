

#include <DX3D/Entity/FogComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>


FogComponent::FogComponent() = default;

FogComponent::~FogComponent()
{
	try
	{
		m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
	}
	catch (...)
	{
		// Handle any exceptions that may occur during cleanup
	}
}

void FogComponent::setData(const Vector4D& color, f32 start, f32 end)
{
	m_color = color;
	m_start = start;
	m_end = end;
}

Vector4D FogComponent::getColor()
{
	return m_color;
}

f32 FogComponent::getStart()
{
	return m_start;
}

f32 FogComponent::getEnd()
{
	return m_end;
}

void FogComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
