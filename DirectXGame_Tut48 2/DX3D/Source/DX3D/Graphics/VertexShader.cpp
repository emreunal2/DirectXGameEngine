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

#include <DX3D/Graphics/VertexShader.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/ShaderInclude.h>

#include <d3dcompiler.h>
#include <exception>

VertexShader::VertexShader(const wchar_t* full_path, const char* entryPoint ,RenderSystem * system): m_system(system)
{
	Microsoft::WRL::ComPtr<ID3DBlob>  blob;
	Microsoft::WRL::ComPtr<ID3DBlob>  errorBlob;
	ShaderInclude shaderInclude(full_path);

	D3DCompileFromFile(full_path, nullptr, &shaderInclude,
		entryPoint, "vs_5_0", 0, 0, &blob, &errorBlob);

	if (errorBlob)
		DX3DWarning("Vertex Shader " << full_path << " compiled with errors: \n" << (char*)errorBlob->GetBufferPointer());
	if (!blob)
		DX3DError("Vertex Shader " << full_path << " not created successfully.");
	if (FAILED(m_system->m_d3d_device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_vs)))
		DX3DError("Vertex Shader " << full_path << " not created successfully.");
}



