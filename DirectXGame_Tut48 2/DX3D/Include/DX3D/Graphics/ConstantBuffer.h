

#pragma once
#include <d3d11.h> 
#include <wrl.h>
#include <DX3D/Prerequisites.h>

class ConstantBuffer
{
public:
	ConstantBuffer(const void* buffer, ui32 size_buffer,RenderSystem * system);
	void update(const DeviceContextPtr& context, const void* buffer);
	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	RenderSystem * m_system = nullptr;
private:
	friend class DeviceContext;
};