#include "pchOrange.h"
#include "Texture.h"

#include <glad/glad.h>


namespace Orange
{
	void Texture::Setup()
	{
		glGenTextures(1, &m_RendererID);

		this->Bind();

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	Texture::Texture(uint32_t width, uint32_t height, const uint8_t* data, ImageFormat format)
		:m_Width(width), m_Height(height)
	{
		Setup();

		int gl_format = ConvertFormat(format);
		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(const std::shared_ptr<Image>& image)
		:m_Image(image), m_RendererID(0)
	{
		Setup();

		m_Width = image->GetWidth();
		m_Height = image->GetHeight();

		int gl_format = ConvertFormat(image->GetFormat());

		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, m_Width, m_Height, 0, gl_format, GL_UNSIGNED_BYTE, image->GetData());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(std::string_view filePath)
		:Texture(Image::CreateShared(filePath))
	{
	}

	const std::string& Texture::GetFilepath() const
	{
		if (m_Image)
			return m_Image->GetFilepath();
		return "";
	}

	float Texture::GetAspectRatio() const
	{
		return static_cast<float>(m_Width) / static_cast<float>(m_Height);
	}

	uint32_t Texture::GetWidth() const
	{
		return m_Width;
	}

	uint32_t Texture::GetHeight() const
	{
		return m_Height;
	}

	uint32_t Texture::GetID() const
	{
		return m_RendererID;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture::BindUnit(uint32_t unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}

	std::unique_ptr<Texture> Texture::CreateUnique(uint32_t width, uint32_t height, const uint8_t* data, ImageFormat format)
	{
		return std::make_unique<Texture>(width, height,data, format);
	}

	std::shared_ptr<Texture> Texture::CreateShared(uint32_t width, uint32_t height, const uint8_t* data, ImageFormat format)
	{
		return std::make_shared<Texture>(width, height, data, format);
	}

	std::unique_ptr<Texture> Texture::CreateUnique(std::string_view filePath)
	{
		return std::make_unique<Texture>(filePath);
	}

	std::shared_ptr<Texture> Texture::CreateShared(std::string_view filePath)
	{
		return std::make_shared<Texture>(filePath);
	}

	int Texture::ConvertFormat(ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::R:
			return GL_RED;
		case ImageFormat::RG:
			return GL_RG;
		case ImageFormat::RGB:
			return GL_RGB;
		case ImageFormat::RGBA:
			return GL_RGBA;
		}
		return 0;
	}
}