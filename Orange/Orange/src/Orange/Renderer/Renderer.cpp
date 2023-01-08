#include "pchOrange.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Orange
{
	Renderer* Renderer::s_Instance = nullptr;
	Renderer::Renderer()
	{
		float vertices[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			-0.5f,  0.5f,
			-0.5f,  0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
		};

		glGenBuffers(1, &m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &m_VAO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		m_Shader = std::make_unique<Shader>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
	}

	void Renderer::Initialize()
	{
		ORANGE_ASSERT(!s_Instance, "Renderer already initialized!");
		s_Instance = new Renderer();
	}

	void Renderer::Terminate()
	{
		delete s_Instance;
	}

	void Renderer::Begin()
	{
		auto& ins = s_Instance;

		ins->m_Shader->Use();
		glBindVertexArray(ins->m_VAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Renderer::End()
	{
		auto& ins = s_Instance;

		glBindVertexArray(0);
		ins->m_Shader->Use(false);
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}
}