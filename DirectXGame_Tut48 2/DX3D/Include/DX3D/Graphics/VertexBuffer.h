

#pragma once
#include <d3d11.h> 
#include <wrl.h>
#include <DX3D/Prerequisites.h>

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, ui32 size_vertex, ui32 size_list,
		RenderSystem * system);
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
	ui32 getSizeVertexList();
private:
	ui32 m_size_vertex;
	ui32 m_size_list;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;
	RenderSystem * m_system = nullptr;
private:
	friend class DeviceContext;
};

