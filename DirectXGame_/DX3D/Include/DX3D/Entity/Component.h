

#pragma once
#include <DX3D/Prerequisites.h>


class Component
{
public:
	Component();
	virtual ~Component();

	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	void release();

	Entity* getEntity();
public:
	virtual void onCreateInternal();
public:
	size_t m_typeId = 0;
	Entity* m_entity = nullptr;

	friend class Entity;
};

