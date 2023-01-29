#include "pch.h"


class TileAppLayer : public Orange::Layer
{
public:
	TileAppLayer()
	{
		Orange::ImGuiDevice::ShowDockspace();

		m_FrameBuffer = std::make_shared<Orange::FrameBuffer>();
		Orange::Renderer::SetFrameBuffer(m_FrameBuffer);

		m_Tilemap = std::make_shared<Orange::Tilemap>();
		m_Tileset = Orange::Tileset::CreateShared("Assets/Images/tileset.png", Orange::Float2(16, 16));
		m_Texture = Orange::Texture::CreateShared("Assets/Images/tileset.png");
	
		Orange::App::GetCamera()->SetWidth(20.0f);

		auto& tilemap = *m_Tilemap;
		tilemap[0][0] = Orange::Tile::CreateShared(m_Tileset, 4, 8);
		tilemap[1][1] = Orange::Tile::CreateShared(m_Tileset, 4, 8);
		tilemap[2][2] = Orange::Tile::CreateShared(m_Tileset, 4, 8);
	
		Orange::App::GetScene()->PushChild(m_Tilemap);
	}

	~TileAppLayer()
	{
		
	}

	virtual void OnUpdate() override
	{
		//Orange::Renderer::DrawQuad(Orange::Float2(0.0f, 0.0f));

		//Orange::Renderer::DrawTexture(m_Texture, Orange::Float2(0.0f, 0.0f));

		//Orange::Renderer::DrawTile(m_Tileset, 4, 8, Orange::Float2(0.0f, 0.0f));
	}

	virtual void OnEvent(const Orange::Event& e) override
	{
		if (e.GetType() == Orange::EventType::KeyPress)
		{
			auto& ev = e.Cast<Orange::KeyPressEvent>();
			if (ev.GetKey() == ORANGE_KEY_LEFT)
			{
				Orange::App::GetCamera()->GetX() -= 0.1f;
			}
			if (ev.GetKey() == ORANGE_KEY_RIGHT)
			{
				Orange::App::GetCamera()->GetX() += 0.1f;
			}
			if (ev.GetKey() == ORANGE_KEY_DOWN)
			{
				Orange::App::GetCamera()->GetY() -= 0.1f;
			}
			if (ev.GetKey() == ORANGE_KEY_UP)
			{
				Orange::App::GetCamera()->GetY() += 0.1f;
			}
		}
	}

	virtual void OnImGui() override
	{
		ImGui::ShowDemoWindow((bool*)0);

		Orange::ImGuiDevice::RenderWindow(m_FrameBuffer);

		ImGui::Begin("Scene");

		Orange::App::GetScene()->ToImGuiTree();

		ImGui::End();
	}
private:
	std::shared_ptr<Orange::Tilemap> m_Tilemap;
	std::shared_ptr<Orange::Tileset> m_Tileset;
	std::shared_ptr<Orange::Texture> m_Texture;
	std::shared_ptr<Orange::FrameBuffer> m_FrameBuffer;
};


class TileApp : public Orange::App
{
public:
	TileApp()
	{
		PushLayer(new TileAppLayer());
	}
};


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<TileApp>();
}

