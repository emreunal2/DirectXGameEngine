

#include <DX3D/Graphics/PixelShader.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/ShaderInclude.h>

#include <d3dcompiler.h>
#include <exception>

PixelShader::PixelShader(const wchar_t* full_path, const char* entryPoint,RenderSystem * system) : m_system(system)
{
	Microsoft::WRL::ComPtr<ID3DBlob>  blob;
	Microsoft::WRL::ComPtr<ID3DBlob>  errorBlob;
	ShaderInclude shaderInclude(full_path);

	D3DCompileFromFile(full_path, nullptr, &shaderInclude,
		entryPoint, "ps_5_0", 0, 0, &blob, &errorBlob);

	if (errorBlob)
	{

	}
	if (!blob)
	{

	}
	if (FAILED(m_system->m_d3d_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_ps)))
	{

	}
}

