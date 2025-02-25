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
#include <set>


class PhysicsEngine
{
public:
	PhysicsEngine(Game* game);
	virtual ~PhysicsEngine();

	void update();
public:
	void addComponent(Component* component);
	void removeComponent(Component* component);
private:
	void _processTerrainPlayerCollision(TerrainComponent* terrain, PlayerControllerComponent* player);
	void _processSpherePlayerCollision(SphereColliderComponent* sphere, PlayerControllerComponent* player);
	void _processSphereSphereCollision(SphereColliderComponent* sphere1, SphereColliderComponent* sphere2);
	void _processTerrainSphereCollision(TerrainComponent* terrain, SphereColliderComponent* sphere);
private:
	Game* m_game = nullptr;

	std::set<Component*> m_components;
	std::set<Component*> m_checkedComponents;

	PlayerControllerComponent* m_player = nullptr;
};

