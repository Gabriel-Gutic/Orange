#include "pchOrange.h"
#include "Tilemap.h"


namespace Orange
{
	Tilemap::Tilemap(uint32_t rows, uint32_t cols)
	{
		Resize(rows, cols);
	}

	void Tilemap::Resize(uint32_t rows, uint32_t cols)
	{
		m_Tiles.resize(rows);
		for (uint32_t i = 0; i < rows; i++)
			m_Tiles[i].resize(cols, nullptr);
	}

	std::vector<std::shared_ptr<Tile>>& Tilemap::operator[](size_t index)
	{
		return m_Tiles[index];
	}

	const std::vector<std::shared_ptr<Tile>>& Tilemap::operator[](size_t index) const
	{
		return m_Tiles[index];
	}

	uint32_t Tilemap::GetRows() const
	{
		return m_Tiles.size();
	}

	uint32_t Tilemap::GetColumns() const
	{
		return m_Tiles.size();
	}
}