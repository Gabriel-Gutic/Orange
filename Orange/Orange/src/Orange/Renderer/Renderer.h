#pragma once
#include "Shader.h"


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
		unsigned int m_VBO, m_VAO;
		std::unique_ptr<Shader> m_Shader;


		static Renderer* s_Instance;
	};
}
