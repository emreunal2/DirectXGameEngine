

#pragma once
#include <DX3D/Prerequisites.h>
#include <map>
#include <set>

class World
{
public:
	explicit World(Game* game);
	~World();
	World(const World&) = delete;
	World& operator=(const World&) = delete;
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

