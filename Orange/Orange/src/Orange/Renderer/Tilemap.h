#pragma once
#include "Orange/Core/Object.h"
#include "Tile.h"


namespace Orange
{
	class Tilemap : public Object
	{
	public:
		Tilemap(uint32_t rows = 16, uint32_t cols = 16);
		virtual ~Tilemap() = default;

		void Resize(uint32_t rows, uint32_t cols);

		std::vector<std::shared_ptr<Tile>>& operator[](size_t index);
		const std::vector<std::shared_ptr<Tile>>& operator[](size_t index) const;

		uint32_t GetRows() const;
		uint32_t GetColumns() const;
	protected:
		std::vector<std::vector<std::shared_ptr<Tile>>> m_Tiles;
	};
}
