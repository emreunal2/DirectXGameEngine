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
#include <unordered_map>
#include <string>
#include <DX3D/Prerequisites.h>
#include <DX3D/Resource/Resource.h>

class ResourceManager
{
public:
	ResourceManager(Game* game);
	~ResourceManager();

	template<typename T>
	std::shared_ptr<T> createResourceFromFile(const wchar_t* file_path)
	{
		return std::dynamic_pointer_cast<T>(createResourceFromFileConcrete(file_path));
	}

	Game* getGame();
private:
	ResourcePtr createResourceFromFileConcrete(const wchar_t * file_path);
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
	Game* m_game = nullptr;
};

