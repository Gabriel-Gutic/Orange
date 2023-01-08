#pragma once
#include "VertexBuffer.h"


namespace Orange
{
	class VertexArray
	{
	public:
		VertexArray(const std::initializer_list<uint8_t>& layout);
		virtual ~VertexArray();

		void Bind();
		void Unbind();
		uint32_t GetID() const;

		void SetVertexBuffer(std::unique_ptr<VertexBuffer>&& vb);
		std::unique_ptr<VertexBuffer>& GetVertexBuffer();
		const std::unique_ptr<VertexBuffer>& GetVertexBuffer() const;

		static std::unique_ptr<VertexArray> CreateUnique(const std::initializer_list<uint8_t>& layout);
		static std::shared_ptr<VertexArray> CreateShared(const std::initializer_list<uint8_t>& layout);
	private:
		uint32_t m_RendererID;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
	};
}
