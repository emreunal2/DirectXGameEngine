

#include <DX3D/Graphics/PixelShader.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/ShaderInclude.h>

#include <d3dcompiler.h>
#include <exception>

PixelShader::PixelShader(const wchar_t* full_path, const char* entryPoint,RenderSystem * system) : m_system(system)
{
	Microsoft::WRL::ComPtr<ID3DBlob>  glob1;
	Microsoft::WRL::ComPtr<ID3DBlob>  errorBlob;
	ShaderInclude shaderInclude(full_path);

	D3DCompileFromFile(full_path, nullptr, &shaderInclude,
		entryPoint, "ps_5_0", 0, 0, &glob1, &errorBlob);

	if (errorBlob)
	{

	}
	if (!glob1)
	{

	}
	if (FAILED(m_system->m_d3d_device->CreatePixelShader(glob1->GetBufferPointer(), glob1->GetBufferSize(), nullptr, &m_ps)))
	{

	}
}

