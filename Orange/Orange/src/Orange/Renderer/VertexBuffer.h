#pragma once


namespace Orange
{
	enum class BufferType
	{
		Static = 0,
		Dynamic = 1,
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(BufferType type, const void* data = nullptr, size_t size = 0);
		virtual ~VertexBuffer();

		void Bind();
		void Unbind();
		uint32_t GetID() const;

		template <typename T, size_t SIZE>
		void SetData(const std::array<T, SIZE>& data, size_t count);

		void SetData(const void* data, size_t size);

		static std::unique_ptr<VertexBuffer> CreateUnique(BufferType type, const void* data = nullptr, size_t size = 0);
		static std::shared_ptr<VertexBuffer> CreateShared(BufferType type, const void* data = nullptr, size_t size = 0);
	private:
		uint32_t m_RendererID;
		BufferType m_Type;
	};

	template<typename T, size_t SIZE>
	inline void VertexBuffer::SetData(const std::array<T, SIZE>& data, size_t count)
	{
		SetData(data.data(), count * sizeof(T));
	}
}
