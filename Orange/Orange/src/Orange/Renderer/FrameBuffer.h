#pragma once
#include "Texture.h"


namespace Orange
{
	class FrameBuffer
	{
	public:
		FrameBuffer(uint32_t width = 1280, uint32_t height = 720);
		virtual ~FrameBuffer();

		uint32_t GetID() const;
		const std::shared_ptr<Texture>& GetTexture() const;

		void Bind() const;
		void Unbind() const;

		const UInt2& GetSize() const;
		void SetSize(uint32_t width, uint32_t height);
	protected:
		uint32_t m_RendererID;
		uint32_t m_RenderBuffer;

		std::shared_ptr<Texture> m_Texture;
		UInt2 m_Size;
	};
}
