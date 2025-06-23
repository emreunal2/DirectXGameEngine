

#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <exception>

IndexBuffer::IndexBuffer(const void* list_indices, ui32 size_list,RenderSystem * system) : m_system(system) , m_buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::runtime_error("IndexBuffer not created successfully");
	}
}


ui32 IndexBuffer::getSizeIndexList()
{
	return this->m_size_list;
}


