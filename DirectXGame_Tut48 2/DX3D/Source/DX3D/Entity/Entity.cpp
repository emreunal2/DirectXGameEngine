/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <DX3D/Entity/Entity.h>
#include <DX3D/Entity/Component.h>
#include <DX3D/Entity/TransformComponent.h>

#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>


Entity::Entity()
{
	m_transform = createComponent<TransformComponent>();
}

Entity::~Entity()
{
}

void Entity::release()
{
	m_world->removeEntity(this);
}

void Entity::createComponentInternal(Component* component, size_t id)
{
	auto compPtr = std::unique_ptr<Component>(component);
	m_components.emplace(id, std::move(compPtr));
	component->m_typeId = id;
	component->m_entity = this;

	component->onCreateInternal();
}

Component* Entity::getComponentInternal(size_t id)
{
	auto it = m_components.find(id);
	if (it == m_components.end()) return nullptr;
	return it->second.get();
}

void Entity::removeComponent(size_t id)
{
	m_components.erase(id);
}

World* Entity::getWorld()
{
	return m_world;
}

InputSystem* Entity::getInputSystem()
{
	return m_world->getGame()->getInputSystem();
}

TransformComponent* Entity::getTransform()
{
	return m_transform;
}
