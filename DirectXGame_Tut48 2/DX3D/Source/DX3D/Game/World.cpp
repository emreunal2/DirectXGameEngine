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

#include <DX3D/Game/World.h>
#include <DX3D/Entity/Entity.h>

World::World(Game* game): m_game(game)
{
}

World::~World()
{
}

void World::update(f32 deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->m_typeId].erase(e);
	}
	m_entitiesToDestroy.clear();

	for (auto&& [typeId, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			ptr->onUpdate(deltaTime);
		}
	}

}

Game* World::getGame()
{
	return m_game;
}

void World::clear()
{
	m_entitiesToDestroy.clear();
	m_entities.clear();
}

void World::createEntityInternal(Entity* entity, size_t id)
{
	auto entityPtr = std::unique_ptr<Entity>(entity);
	m_entities[id].emplace(entity, std::move(entityPtr));
	entity->m_typeId = id;
	entity->m_world = this;

	entity->onCreate();
}

void World::removeEntity(Entity* entity)
{
	m_entitiesToDestroy.emplace(entity);
}
