

#pragma once
#include <d3d11.h> 
#include <wrl.h>
#include <DX3D/Prerequisites.h>

class IndexBuffer
{
public:
	IndexBuffer(const void* list_indices, ui32 size_list,RenderSystem * system);
	explicit  IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
	ui32 getSizeIndexList();
private:
	ui32 m_size_list;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	RenderSystem * m_system = nullptr;
private:
	friend class DeviceContext;
};