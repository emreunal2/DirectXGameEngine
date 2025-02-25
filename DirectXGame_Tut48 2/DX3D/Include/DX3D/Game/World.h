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

#pragma once
#include <DX3D/Prerequisites.h>
#include <map>
#include <set>

class World
{
public:
	World(Game* game);
	~World();

	template <typename T>
	T* createEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity class");
		auto id = typeid(T).hash_code();
		auto e = new T();
		createEntityInternal(e, id);
		return e;
	}


	void update(f32 deltaTime);


	Game* getGame();

	void clear();


private:
	void createEntityInternal(Entity* entity, size_t id);
	void removeEntity(Entity* entity);
private:
	std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;
	std::set<Entity*> m_entitiesToDestroy;
	Game* m_game = nullptr;

	friend class Entity;
};

