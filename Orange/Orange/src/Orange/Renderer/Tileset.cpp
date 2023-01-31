#include "pchOrange.h"
#include "Tileset.h"


namespace Orange
{
	Tileset::Tileset(std::string_view filepath, const Float2& tileSize, float space)
		:m_Filepath(filepath), m_TileSize(tileSize), m_Space(space)
	{
		if (File::Exists(filepath))
		{
			m_Texture = Texture::CreateShared(filepath);

		}
		else
		{
			ORANGE_ERROR("File '{0}' not found!");
		}
		CalculateTileCount();
	}

	Tileset::~Tileset()
	{
	}

	std::shared_ptr<Texture>& Tileset::GetTexture()
	{
		return m_Texture;
	}

	const std::shared_ptr<Texture>& Tileset::GetTexture() const
	{
		return m_Texture;
	}

	float Tileset::GetAspectRatio() const
	{
		return m_TileSize.x / m_TileSize.y;
	}

	const UInt2& Tileset::GetSize() const
	{
		return m_Size;
	}

	uint32_t Tileset::GetRows() const
	{
		return m_Size.x;
	}

	uint32_t Tileset::GetColumns() const
	{
		return m_Size.y;
	}

	std::array<std::array<Float2, 2>, 2> Tileset::GetTileCoords(uint32_t row, uint32_t column) const
	{
		std::array<std::array<Float2, 2>, 2> arr;

		float w = m_TileSize.x / m_Texture->GetWidth();
		float h = m_TileSize.y / m_Texture->GetHeight();

		float left = m_Space + (m_Space + w) * column;
		float bottom = 1.0f - (m_Space + h) * (row + 1);
		float right = (m_Space + w) * (column + 1);
		float top = 1.0f - m_Space * (row + 1) - h * row;

		arr[0][0] = Float2(left, bottom);
		arr[0][1] = Float2(left, top);
		arr[1][0] = Float2(right, bottom);
		arr[1][1] = Float2(right, top);
		return arr;
	}

	std::shared_ptr<Tileset> Tileset::CreateShared(std::string_view filepath, const Float2& tileSize, float space)
	{
		return std::make_shared<Tileset>(filepath, tileSize, space);
	}

	std::unique_ptr<Tileset> Tileset::CreateUnique(std::string_view filepath, const Float2& tileSize, float space)
	{
		return std::make_unique<Tileset>(filepath, tileSize, space);
	}

	void Tileset::CalculateTileCount()
	{
		if (m_Texture)
		{
			m_Size.x = (m_Texture->GetHeight() - m_Space) / (m_TileSize.y + m_Space);
			m_Size.y = (m_Texture->GetWidth()  - m_Space) / (m_TileSize.x + m_Space);
		}
	}
}