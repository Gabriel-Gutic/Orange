#pragma once
#include "Shader.h"
#include "VertexArray.h"


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

		static Renderer* Get();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;

		static Renderer* s_Instance;
	};
}
