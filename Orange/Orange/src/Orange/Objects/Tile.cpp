#include "pchOrange.h"
#include "Tile.h"


namespace Orange
{
	Tile::Tile(const std::shared_ptr<Tileset>& set, uint32_t row, uint32_t column)
		:GameObject("Tile"), m_Set(set), m_Row(row), m_Column(column)
	{
	}

	std::shared_ptr<Tileset>& Tile::GetSet()
	{
		return m_Set;
	}

	const std::shared_ptr<Tileset>& Tile::GetSet() const
	{
		return m_Set;
	}

	uint32_t Tile::GetRow() const
	{
		return m_Row;
	}

	uint32_t Tile::GetColumn() const
	{
		return m_Column;
	}

	std::shared_ptr<Tile> Tile::CreateShared(const std::shared_ptr<Tileset>& set, uint32_t row, uint32_t column)
	{
		return std::make_shared<Tile>(set, row, column);
	}

	std::unique_ptr<Tile> Tile::CreateUnique(const std::shared_ptr<Tileset>& set, uint32_t row, uint32_t column)
	{
		return std::make_unique<Tile>(set, row, column);
	}
}