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

#include <DX3D/Resource/ResourceManager.h>
#include <DX3D/Resource/Mesh.h>
#include <DX3D/Resource/Texture.h>
#include <DX3D/Resource/Material.h>
#include <DX3D/Resource/Font.h>
#include <filesystem>


ResourceManager::ResourceManager(Game* game):m_game(game)
{
}


ResourceManager::~ResourceManager()
{
}

Game* ResourceManager::getGame()
{
	return m_game;
}

ResourcePtr ResourceManager::createResourceFromFileConcrete(const wchar_t * file_path)
{
	std::filesystem::path resourcePath = file_path;
	auto ext = resourcePath.extension();


	auto it = m_map_resources.find(file_path);

	if (it != m_map_resources.end())
	{
		auto mat = std::dynamic_pointer_cast<Material>(it->second);
		if (mat) return std::make_shared<Material>(mat, this);
		return it->second;
	}

	if (!std::filesystem::exists(resourcePath)) return ResourcePtr();

	ResourcePtr resPtr;

	if (!ext.compare(L".obj"))
		resPtr = std::make_shared<Mesh>(resourcePath.c_str(), this);
	else if (!ext.compare(L".jpg") || !ext.compare(L".png") || !ext.compare(L".bmp"))
		resPtr = std::make_shared<Texture>(resourcePath.c_str(), this);
	else if (!ext.compare(L".hlsl") || !ext.compare(L".fx"))
		resPtr = std::make_shared<Material>(resourcePath.c_str(), this);
	else if (!ext.compare(L".font"))
		resPtr = std::make_shared<Font>(resourcePath.c_str(), this);

	if (resPtr)
	{
		m_map_resources.emplace(file_path, resPtr);
		return resPtr;
	}

	return nullptr;
}

