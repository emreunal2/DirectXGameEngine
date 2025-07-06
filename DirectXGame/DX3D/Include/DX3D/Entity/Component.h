

#pragma once
#include <DX3D/Prerequisites.h>


class Component
{
public:
	Component();
	virtual ~Component();

	void release();

	Entity* getEntity();
protected:
	virtual void onCreateInternal();
protected:
	size_t m_typeId = 0;
	Entity* m_entity = nullptr;

	friend class Entity;
};

