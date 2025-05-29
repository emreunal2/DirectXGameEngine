

#include <DX3D/Entity/ImageComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Resource/Texture.h>
#include <DX3D/Graphics/Texture2D.h>

ImageComponent::ImageComponent()
{
}

ImageComponent::~ImageComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void ImageComponent::setImage(const TexturePtr& image)
{
	m_image = image;
	m_size = m_image->getTexture()->getSize();
}

const TexturePtr& ImageComponent::getImage()
{
	return m_image;
}

void ImageComponent::setSize(const Rect& size)
{
	m_size = size;
}

Rect ImageComponent::getSize()
{
	return m_size;
}

void ImageComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
