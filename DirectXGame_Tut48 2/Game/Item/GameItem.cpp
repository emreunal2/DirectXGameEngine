

#include "GameItem.h"

GameItem::GameItem()
{
}

GameItem::~GameItem()
{
}

void GameItem::setPosition(const Vector3D& position)
{
	m_pos = position;
}

void GameItem::setDirection(const Vector3D& direction)
{
	//m_direction = Vector3D::normalize(direction);
	m_direction = direction;
}

void GameItem::onCreate()
{
	Entity::onCreate();
	//m_collider = createComponent<SphereColliderComponent>();
	//m_collider->setRadius(10.0f);
}

void GameItem::onUpdate(f32 deltaTime)
{
	Entity::onUpdate(deltaTime);
}

Vector3D GameItem::getPosition()
{
	return m_pos;
}
Vector3D GameItem::getDirection()
{
	return m_direction;
}
