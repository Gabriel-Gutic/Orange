#pragma once
#include "VertexBuffer.h"


namespace Orange
{
	class VertexArray
	{
	public:
		VertexArray(const std::initializer_list<uint8_t>& layout, const std::shared_ptr<VertexBuffer>& vb);
		virtual ~VertexArray();

		void Bind();
		void Unbind();
		uint32_t GetID() const;

		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vb);
		std::shared_ptr<VertexBuffer>& GetVertexBuffer();
		const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const;

		static std::unique_ptr<VertexArray> CreateUnique(const std::initializer_list<uint8_t>& layout, const std::shared_ptr<VertexBuffer>& vb);
		static std::shared_ptr<VertexArray> CreateShared(const std::initializer_list<uint8_t>& layout, const std::shared_ptr<VertexBuffer>& vb);
	private:
		uint32_t m_RendererID;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
	};
}
