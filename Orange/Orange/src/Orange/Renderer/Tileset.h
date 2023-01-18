#pragma once
#include "Texture.h"


namespace Orange
{
	class Tileset
	{
	public:
		Tileset(std::string_view filepath, const Float2& tileSize, float space = 0.0f);
		virtual ~Tileset();

		std::shared_ptr<Texture>& GetTexture();
		const std::shared_ptr<Texture>& GetTexture() const;

		float GetAspectRatio() const;

		std::array<std::array<Float2, 2>, 2> GetTileCoords(uint32_t row, uint32_t column) const;
	
		static std::shared_ptr<Tileset> CreateShared(std::string_view filepath, const Float2& tileSize, float space = 0.0f);
		static std::unique_ptr<Tileset> CreateUnique(std::string_view filepath, const Float2& tileSize, float space = 0.0f);
	private:
		void CalculateTileCount();
	private:
		std::string m_Filepath;
		std::shared_ptr<Texture> m_Texture;

		Float2 m_TileSize;
		float m_Space;

		UInt2 m_TileCount;
	};
}
