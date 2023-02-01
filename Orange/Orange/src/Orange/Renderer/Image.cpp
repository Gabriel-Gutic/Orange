#include "pchOrange.h"
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


namespace Orange
{
	Image::Image(std::string_view filepath)
		:m_Filepath(filepath), m_Data(nullptr), m_Width(0), m_Height(0), m_Format(ImageFormat::None)
	{
		ORANGE_ASSERT(File::Exists(filepath), "Image '{0}' not found!", filepath);

		stbi_set_flip_vertically_on_load(true);

		int nrChannels;
		m_Data = stbi_load(filepath.data(), &m_Width, &m_Height, &nrChannels, 4);
		nrChannels = 4;

		ORANGE_ASSERT(m_Data, "Failed to load image from path: {0}", filepath);

		m_Format = static_cast<ImageFormat>(nrChannels);
	}

	Image::~Image()
	{
		stbi_image_free(m_Data);
	}

	const std::string& Image::GetFilepath() const
	{
		return m_Filepath;
	}

	uint8_t* Image::GetData()
	{
		return m_Data;
	}

	const uint8_t* Image::GetData() const
	{
		return m_Data;
	}

	int Image::GetWidth() const
	{
		return m_Width;
	}

	int Image::GetHeight() const
	{
		return m_Height;
	}

	ImageFormat Image::GetFormat() const
	{
		return m_Format;
	}

	int Image::GetSize() const
	{
		return static_cast<int>(m_Format) * 4 * m_Width * m_Height;
	}

	std::shared_ptr<Image> Image::CreateShared(std::string_view filePath)
	{
		return std::make_shared<Image>(filePath);
	}

	std::unique_ptr<Image> Image::CreateUnique(std::string_view filePath)
	{
		return std::make_unique<Image>(filePath);
	}
}