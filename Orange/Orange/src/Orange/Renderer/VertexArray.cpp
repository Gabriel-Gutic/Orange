#include "pchOrange.h"
#include "VertexArray.h"

#include <glad/glad.h>


namespace Orange
{
	VertexArray::VertexArray(const std::initializer_list<uint8_t>& layout)
		:m_VertexBuffer(nullptr)
	{
		glGenVertexArrays(1, &m_RendererID);

		Bind();

		size_t size = 0, vertexSize = 0;

		for (const auto& el : layout)
		{
			ORANGE_ASSERT(el <= 4, "Invalid layout with component size {0}", el);
			vertexSize += el * sizeof(float);
		}

		size_t i = 0;
		for (const auto& el : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, el, GL_FLOAT, GL_FALSE, vertexSize, (const void*)size);
			size += el * sizeof(float);
			i++;
		}

		Unbind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	uint32_t VertexArray::GetID() const
	{
		return m_RendererID;
	}

	void VertexArray::SetVertexBuffer(std::unique_ptr<VertexBuffer>&& vb)
	{
		if (vb)
		{
			m_VertexBuffer = std::move(vb);
		}
	}

	std::unique_ptr<VertexBuffer>& VertexArray::GetVertexBuffer()
	{
		return m_VertexBuffer;
	}

	const std::unique_ptr<VertexBuffer>& VertexArray::GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}

	std::unique_ptr<VertexArray> VertexArray::CreateUnique(const std::initializer_list<uint8_t>& layout)
	{
		return std::make_unique<VertexArray>(layout);
	}

	std::shared_ptr<VertexArray> VertexArray::CreateShared(const std::initializer_list<uint8_t>& layout)
	{
		return std::make_shared<VertexArray>(layout);
	}
}