

#include <DX3D/Entity/LightComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>

LightComponent::LightComponent()
{
}

LightComponent::~LightComponent()
{
	try {
		m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
	}
	catch (...) {
		//tests
	}
}

void LightComponent::setColor(const Vector4D& color)
{
	m_color = color;
}

Vector4D LightComponent::getColor()
{
	return m_color;
}

void LightComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
