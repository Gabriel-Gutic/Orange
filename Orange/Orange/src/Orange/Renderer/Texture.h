#pragma once
#include "Image.h"


namespace Orange
{
	class Texture
	{
	private:
		void Setup();
	public:
		Texture(uint32_t width, uint32_t height, const uint8_t* data, ImageFormat format);
		Texture(const std::shared_ptr<Image>& image = nullptr);
		Texture(std::string_view filePath);
		virtual ~Texture() = default;

		const std::string& GetFilepath() const;
		float GetAspectRatio() const;
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		uint32_t GetID() const;

		void Bind() const;
		void BindUnit(uint32_t unit) const;
	public:
		static std::unique_ptr<Texture> CreateUnique(uint32_t width, uint32_t height, const uint8_t* data = nullptr, ImageFormat format = ImageFormat::RGBA);
		static std::shared_ptr<Texture> CreateShared(uint32_t width, uint32_t height, const uint8_t* data = nullptr, ImageFormat format = ImageFormat::RGBA);
		static std::unique_ptr<Texture> CreateUnique(std::string_view filePath);
		static std::shared_ptr<Texture> CreateShared(std::string_view filePath);
	private:
		static int ConvertFormat(ImageFormat format);
	private:
		uint32_t m_RendererID;

		uint32_t m_Width, m_Height;
		std::shared_ptr<Image> m_Image;
	};
}
