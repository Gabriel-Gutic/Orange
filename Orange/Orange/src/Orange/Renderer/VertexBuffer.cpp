#include "pchOrange.h"
#include "VertexBuffer.h"

#include <glad/glad.h>


namespace Orange
{
	VertexBuffer::VertexBuffer(BufferType type, const void* data, size_t size)
		:m_Type(type)
	{
		glGenBuffers(1, &m_RendererID);

		Bind();

		int usage = GL_STATIC_DRAW;
		if (type == BufferType::Dynamic)
			usage = GL_DYNAMIC_DRAW;

		glBufferData(GL_ARRAY_BUFFER, size, data, usage);

		Unbind();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	uint32_t VertexBuffer::GetID() const
	{
		return m_RendererID;
	}

	void VertexBuffer::SetData(const void* data, size_t size)
	{
		if (m_Type == BufferType::Dynamic)
		{
			Bind();
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
			Unbind();
		}
		else
		{
			ORANGE_ERROR("SetData is only allowed for dynamic buffers!");
		}
	}

	std::unique_ptr<VertexBuffer> VertexBuffer::CreateUnique(BufferType type, const void* data, size_t size)
	{
		return std::make_unique<VertexBuffer>(type, data, size);
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::CreateShared(BufferType type, const void* data, size_t size)
	{
		return std::make_shared<VertexBuffer>(type, data, size);
	}
}