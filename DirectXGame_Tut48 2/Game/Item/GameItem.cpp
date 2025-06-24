

#include "GameItem.h"

GameItem::GameItem() = default;

GameItem::~GameItem() = default;

void GameItem::setPosition(const Vector3D& position)
{
	m_pos = position;
}

void GameItem::setDirection(const Vector3D& direction)
{
	m_direction = Vector3D::normalize(direction);
}

void GameItem::onCreate()
{
	Entity::onCreate();
	m_collider = createComponent<SphereColliderComponent>();
	m_collider->setRadius(4.0f);
}

void GameItem::onUpdate(f32 deltaTime)
{
	Entity::onUpdate(deltaTime);
}
