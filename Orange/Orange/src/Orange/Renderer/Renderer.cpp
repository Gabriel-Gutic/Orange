#include "pchOrange.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Vertex.h"
#include "RendererData.h"


namespace Orange
{
	Renderer* Renderer::s_Instance = nullptr;

	struct RendererData
	{
		std::array<Vertex, MAX_VERTEX_NUMBER> Vertices = {};
		uint32_t VertexCounter = 0;
	};
	static RendererData s_Data = {};

	Renderer::Renderer()
	{
		s_Data.Vertices =
		{
			Vertex({-0.5f, -0.5f}, {1.0f, 0.3f, 0.6f, 1.0f}),
			Vertex({ 0.5f, -0.5f}, {1.0f, 0.3f, 0.6f, 1.0f}),
			Vertex({-0.5f,  0.5f}, {1.0f, 0.3f, 0.6f, 1.0f}),
			Vertex({-0.5f,  0.5f}, {1.0f, 0.3f, 0.6f, 1.0f}),
			Vertex({ 0.5f, -0.5f}, {1.0f, 0.3f, 0.6f, 1.0f}),
			Vertex({ 0.5f,  0.5f}, {1.0f, 0.3f, 0.6f, 1.0f}),
		};
		s_Data.VertexCounter = 6;

		m_VertexBuffer = VertexBuffer::CreateUnique(BufferType::Dynamic, nullptr, sizeof(RendererData::Vertices));
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

		Mat3 R = Math::Rotate(0.01f);

		for (auto& vertex : s_Data.Vertices)
		{
			vertex.Position = R * vertex.Position;
		}

		ins->m_Shader->Use();
		ins->m_VertexArray->Bind();

		ins->m_VertexBuffer->Bind();
		ins->m_VertexBuffer->SetData(s_Data.Vertices, s_Data.VertexCounter);
		ins->m_VertexBuffer->Unbind();

		glDrawArrays(GL_TRIANGLES, 0, s_Data.VertexCounter);
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