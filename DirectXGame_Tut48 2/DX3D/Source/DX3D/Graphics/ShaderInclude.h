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
#include <filesystem>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <fstream>
#include <sstream>

class ShaderInclude: public ID3DInclude
{
public:
	ShaderInclude(const std::filesystem::path& shaderPath): m_shaderPath(shaderPath)
	{

	}
	~ShaderInclude()
	{

	}

	virtual HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName,
		LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
	{
		auto includePath = m_shaderPath;
		includePath = includePath.parent_path();
		includePath += "/";
		includePath += pFileName;

		std::ifstream shaderStream(includePath);
		if (shaderStream.is_open())
		{
			std::stringstream sstr;
			sstr << shaderStream.rdbuf();
			auto str = sstr.str();

			char* shaderCode = new char[str.size() + 1];
			memcpy(shaderCode, str.c_str(), str.size() + 1);

			shaderStream.close();

			*ppData = shaderCode;
			*pBytes = (UINT)str.size();

			return S_OK;
		}
		return S_FALSE;
	}
	virtual HRESULT Close(LPCVOID pData)
	{
		delete pData;
		return S_OK;
	}

private:
	std::filesystem::path m_shaderPath;
};