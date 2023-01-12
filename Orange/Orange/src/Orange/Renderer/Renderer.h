#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"


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

		static void DrawTexture(const std::shared_ptr<Texture>& texture, const Float2& position);
		static void DrawQuad(const Float2& center, float side = 1.0f, const FColor& color = FColor::White);

		static Renderer* Get();
	private:
		float GetTextureIndex(const std::shared_ptr<Texture>& texture);
		void Flush();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;

		static Renderer* s_Instance;
	};
}
