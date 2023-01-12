#pragma once


namespace Orange
{
	enum class ImageFormat
	{
		None = 0,
		R = 1,
		RG = 2,
		RGB = 3,
		RGBA = 4,
	};

	class Image
	{
	public:
		Image(std::string_view filePath);
		~Image();

		uint8_t* GetData();
		const uint8_t* GetData() const;
		int GetWidth() const;
		int GetHeight() const;
		ImageFormat GetFormat() const;
		int GetSize() const;
	public:
		static std::shared_ptr<Image> CreateShared(std::string_view filePath);
		static std::unique_ptr<Image> CreateUnique(std::string_view filePath);
	private:
		uint8_t* m_Data;
		int m_Width;
		int m_Height;
		ImageFormat m_Format;
	};
}