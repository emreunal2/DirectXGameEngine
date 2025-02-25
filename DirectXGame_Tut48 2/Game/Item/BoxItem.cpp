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

#include "BoxItem.h"

BoxItem::BoxItem()
{
}

BoxItem::~BoxItem()
{
}

void BoxItem::onCreate()
{
	GameItem::onCreate();
	//Load all the assets
	auto tex = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/spaceship.jpg");
	auto mesh = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/box.obj");
	auto mat = getWorld()->getGame()->getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/GameItem.hlsl");
	//Add the texture to material
	mat->addTexture(tex);

	m_itemMesh = this->createComponent<MeshComponent>();
	//Set the mesh and material into the entity
	m_itemMesh->setMesh(mesh);
	m_itemMesh->addMaterial(mat);

	getTransform()->setScale(Vector3D(5, 5, 5));
	m_collider->setRadius(5.0f);
}

void BoxItem::onUpdate(f32 deltaTime)
{
	GameItem::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;

	m_angle += 3.14f * deltaTime;

	auto pos = m_pos;

	getTransform()->setRotation(Vector3D(0, m_angle * 0.4f, 0));

	if (m_elapsedSeconds > 5.0f)
	{
		m_pos.y += deltaTime * 50.0f;
		getTransform()->setPosition(pos);
	}
	else
	{
		pos.y = m_pos.y + sin(m_angle) * 0.707f;
		getTransform()->setPosition(pos);
	}

}

void BoxItem::onCollision(Component* body1, Component* body2)
{
}

