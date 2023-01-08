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
			-0.5f, -0.5f, 1.0f, 0.3f, 0.6f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.3f, 0.6f, 1.0f,
			-0.5f,  0.5f, 1.0f, 0.3f, 0.6f, 1.0f,
			-0.5f,  0.5f, 1.0f, 0.3f, 0.6f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.3f, 0.6f, 1.0f,
			 0.5f,  0.5f, 1.0f, 0.3f, 0.6f, 1.0f,
		};

		m_VertexBuffer = VertexBuffer::CreateUnique(BufferType::Static, vertices, sizeof(vertices));
		m_VertexBuffer->Bind();
		m_VertexArray = VertexArray::CreateUnique({ 2, 4 });
		m_VertexBuffer->Unbind();

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
		ins->m_VertexArray->Bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Renderer::End()
	{
		auto& ins = s_Instance;

		ins->m_VertexArray->Unbind();
		ins->m_Shader->Use(false);
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}
}