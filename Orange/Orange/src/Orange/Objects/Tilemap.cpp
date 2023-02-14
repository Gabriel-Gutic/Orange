#include "pchOrange.h"
#include "Tilemap.h"

#include "Renderer/Renderer.h"


namespace Orange
{
	Tilemap::Tilemap(
		const std::shared_ptr<Tileset>& tileset, 
		const std::initializer_list<std::initializer_list<int>>& map)
		:GameObject("Tilemap")
	{
		int cols = 0;
		for (auto& line : map)
		{
			if (line.size() > cols)
				cols = line.size();
		}

		Resize(map.size(), cols);

		int i = 0;
		for (auto& line : map)
		{
			int j = 0;
			for (int tileIndex : line)
			{
				if (tileIndex > -1)
					m_Tiles[i][j] = Tile::CreateShared(tileset, tileIndex / tileset->GetColumns(), tileIndex % tileset->GetColumns());
				j++;
			}
			i++;
		}

		SetDrawFunction([](const GameObject& obj) {
			Renderer::DrawTilemap(static_cast<const Tilemap&>(obj));
		});
	}

	Tilemap::Tilemap(uint32_t rows, uint32_t cols)
		:GameObject("Tilemap")
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
		return m_Tiles[0].size();
	}
}