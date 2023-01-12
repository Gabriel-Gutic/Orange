#include "pchOrange.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Vertex.h"
#include "Texture.h"
#include "RendererData.h"


namespace Orange
{
	Renderer* Renderer::s_Instance = nullptr;

	struct RendererData
	{
		std::array<Vertex, MAX_VERTEX_NUMBER> Vertices = {};
		uint32_t VertexCounter = 0;
		std::array<std::shared_ptr<Texture>, MAX_TEXTURE_SLOTS> TextureSlots = {};
		uint32_t TextureSlotCounter = 0;

		const std::array<int, MAX_TEXTURE_SLOTS> TextureUnits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	};
	static RendererData s_Data = {};

	Renderer::Renderer()
	{
		auto vertexBuffer = VertexBuffer::CreateShared(BufferType::Dynamic, nullptr, sizeof(RendererData::Vertices));
		m_VertexArray = VertexArray::CreateUnique({ 2, 4, 2, 1 }, vertexBuffer);

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
	}

	void Renderer::End()
	{
		s_Instance->Flush();
	}

	void Renderer::DrawTexture(const std::shared_ptr<Texture>& texture, const Float2& position)
	{
		if (texture)
		{
			if (s_Data.VertexCounter + 6 >= MAX_VERTEX_NUMBER)
				s_Instance->Flush();

			float aspectRatio = texture->GetAspectRatio();
			float x_radius = 0.5f;
			float y_radius = 0.5f / aspectRatio;

			float texIndex = s_Instance->GetTextureIndex(texture);

			Vertex A(Float2(position.x - x_radius, position.y - y_radius), FColor::White, Float2(0.0f, 0.0f), texIndex);
			Vertex B(Float2(position.x + x_radius, position.y - y_radius), FColor::White, Float2(1.0f, 0.0f), texIndex);
			Vertex C(Float2(position.x + x_radius, position.y + y_radius), FColor::White, Float2(1.0f, 1.0f), texIndex);
			Vertex D(Float2(position.x - x_radius, position.y + y_radius), FColor::White, Float2(0.0f, 1.0f), texIndex);

			s_Data.Vertices[s_Data.VertexCounter++] = A;
			s_Data.Vertices[s_Data.VertexCounter++] = B;
			s_Data.Vertices[s_Data.VertexCounter++] = C;
			s_Data.Vertices[s_Data.VertexCounter++] = A;
			s_Data.Vertices[s_Data.VertexCounter++] = C;
			s_Data.Vertices[s_Data.VertexCounter++] = D;
		}
	}

	void Renderer::DrawQuad(const Float2& center, float side, const FColor& color)
	{
		if (s_Data.VertexCounter + 6 >= MAX_VERTEX_NUMBER)
			s_Instance->Flush();

		float radius = side / 2.0f;

		Vertex A(Float2(center.x - radius, center.y - radius), color);
		Vertex B(Float2(center.x + radius, center.y - radius), color);
		Vertex C(Float2(center.x + radius, center.y + radius), color);
		Vertex D(Float2(center.x - radius, center.y + radius), color);

		s_Data.Vertices[s_Data.VertexCounter++] = A;
		s_Data.Vertices[s_Data.VertexCounter++] = B;
		s_Data.Vertices[s_Data.VertexCounter++] = C;
		s_Data.Vertices[s_Data.VertexCounter++] = A;
		s_Data.Vertices[s_Data.VertexCounter++] = C;
		s_Data.Vertices[s_Data.VertexCounter++] = D;
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}

	void Renderer::Flush()
	{
		auto& ins = s_Instance;

		ins->m_Shader->Use();
		ins->m_VertexArray->Bind();

		ins->m_VertexArray->GetVertexBuffer()->Bind();
		ins->m_VertexArray->GetVertexBuffer()->SetData(s_Data.Vertices, s_Data.VertexCounter);
		ins->m_VertexArray->GetVertexBuffer()->Unbind();

		for (uint32_t i = 0; i < s_Data.TextureSlotCounter; i++)
			s_Data.TextureSlots[i]->BindUnit(i);

		m_Shader->SetIntArray("u_Textures", s_Data.TextureUnits);

		glDrawArrays(GL_TRIANGLES, 0, s_Data.VertexCounter);

		ins->m_VertexArray->Unbind();
		ins->m_Shader->Use(false);

		s_Data.VertexCounter = 0;
	}

	float Renderer::GetTextureIndex(const std::shared_ptr<Texture>& texture)
	{
		float texIndex = -1.0f;
		if (texture)
		{
			// Check if texture allready exist in RendererData.TextureSlots
			for (uint32_t i = 0; i < s_Data.TextureSlotCounter; i++)
			{
				if (texture == s_Data.TextureSlots[i])
					texIndex = static_cast<float>(i);
			}
			// Add the texture to RendererData.TextureSlots if it doesn't exist 
			if (texIndex == -1.0f)
			{
				if (s_Data.TextureSlotCounter >= MAX_TEXTURE_SLOTS)
					Flush();
				texIndex = static_cast<float>(s_Data.TextureSlotCounter);
				s_Data.TextureSlots[s_Data.TextureSlotCounter++] = texture;
			}
		}
		return texIndex;
	}
}