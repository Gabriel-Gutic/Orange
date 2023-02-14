#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Tileset.h"
#include "FrameBuffer.h"

#include "Objects/Tilemap.h"


namespace Orange
{
	class Renderer
	{
	private:
		Renderer();
	public:
		Renderer(const Renderer&) = delete;

		static void Initialize();
		static void Terminate();

		static void Begin();
		static void End();

		static void SetFrameBuffer(const std::shared_ptr<FrameBuffer>& fb);
		static const std::shared_ptr<FrameBuffer>& GetFrameBuffer();

		static void DrawTexture(const std::shared_ptr<Texture>& texture, const Float2& position, float scale = 1.0f);
		static void DrawTile(const std::shared_ptr<Tileset>& tileset, uint32_t row, uint32_t column, const Float2& position, float scale = 1.0f);
		static void DrawTile(const std::shared_ptr<Tile>& tile, const Float2& position, float scale = 1.0f);
		static void DrawSprite(const GameObject& obj);
		static void DrawQuad(const Float2& center, float side = 1.0f, const FColor& color = FColor::White);
		
		static void DrawTilemap(const Tilemap& tilemap);

		static Renderer* Get();
	private:
		float GetTextureIndex(const std::shared_ptr<Texture>& texture);
		void Flush();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		static Renderer* s_Instance;
	};
}
