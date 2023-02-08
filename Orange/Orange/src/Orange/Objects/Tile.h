#pragma once
#include "Object.h"
#include "Renderer/TileSet.h"


namespace Orange
{
	class Tile : Object
	{
	public:
		Tile(const std::shared_ptr<Tileset>& set, uint32_t row, uint32_t column);
		~Tile() = default;

		std::shared_ptr<Tileset>& GetSet();
		const std::shared_ptr<Tileset>& GetSet() const;

		uint32_t GetRow() const;
		uint32_t GetColumn() const;

		static std::shared_ptr<Tile> CreateShared(const std::shared_ptr<Tileset>& set, uint32_t row, uint32_t column);
		static std::unique_ptr<Tile> CreateUnique(const std::shared_ptr<Tileset>& set, uint32_t row, uint32_t column);
	private:
		std::shared_ptr<Tileset> m_Set;
		uint32_t m_Row;
		uint32_t m_Column;
	};
}
