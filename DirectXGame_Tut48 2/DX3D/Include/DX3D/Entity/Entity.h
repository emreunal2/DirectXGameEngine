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

class Entity
{
public:
	Entity();
	virtual ~Entity();
	void release();

	World* getWorld();
	InputSystem* getInputSystem();
	TransformComponent* getTransform();

	template <typename T>
	T* createComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component class");
		auto c = getComponent<T>();
		if (!c)
		{
			auto id = typeid(T).hash_code();
			c = new T();
			createComponentInternal(c, id);
			return c;
		}
		return nullptr;
	}

	template <typename T>
	T* getComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component class");
		auto id = typeid(T).hash_code();
		return (T*)getComponentInternal(id);
	}


protected:
	virtual void onCreate() {}
	virtual void onUpdate(f32 deltaTime) {}
	virtual void onCollision(Component* body1, Component* body2) {}
	virtual void onRelease() {}
private:
	void createComponentInternal(Component* component, size_t id);
	Component* getComponentInternal(size_t id);
	void removeComponent(size_t id);
protected:
	size_t m_typeId = 0;
	World* m_world = nullptr;

	TransformComponent* m_transform = nullptr;
	std::map<size_t, std::unique_ptr<Component>> m_components;
	friend class World;
	friend class Component;
	friend class PhysicsEngine;
};

