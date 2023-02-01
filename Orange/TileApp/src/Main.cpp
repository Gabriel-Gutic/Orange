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

		auto& tilemap = *m_Tilemap;

		tilemap = Orange::Tilemap(m_Tileset, {
			{  0,   1,   2,   3},
			{ 11,  12,  12,  14},
			{ 22,  12,  12,  25},
			{ 11,  12,  12,  14},
			{ 11,  12,  12,  14},
			{132, 133, 134, 135},
			{143, 144, 145, 146},
			});
		tilemap.GetTransform().Position = Orange::Float2(-2.0f, 2.0f);
		//for (int i = 0; i < 4; i++)
		//	for (int j = 0; j < 4; j++)
		//		tilemap[j][i] = Orange::Tile::CreateShared(m_Tileset, i, j);

		Orange::App::GetScene()->PushChild(m_Tilemap);


		//Orange::App::GetWindow()->SetVSync(true);
	}

	~TileAppLayer()
	{

	}

	virtual void OnUpdate(float dt) override
	{
		if (Orange::Input::Keyboard(ORANGE_KEY_F))
		{
			PRINT("FPS: {0}", Orange::App::GetFPS());
		}

		Orange::App::GetCamera()->SetWidth(m_CameraWidth);

		//Orange::Renderer::DrawQuad(Orange::Float2(0.0f, 0.0f));

		//Orange::Renderer::DrawTexture(m_Texture, Orange::Float2(0.0f, 0.0f));

		//Orange::Renderer::DrawTile(m_Tileset, 4, 8, Orange::Float2(0.0f, 0.0f));

		if (Orange::Input::Keyboard(ORANGE_KEY_LEFT))
		{
			Orange::App::GetCamera()->GetX() -= dt * m_CameraSpeed;
		}
		if (Orange::Input::Keyboard(ORANGE_KEY_RIGHT))
		{
			Orange::App::GetCamera()->GetX() += dt * m_CameraSpeed;
		}
		if (Orange::Input::Keyboard(ORANGE_KEY_DOWN))
		{
			Orange::App::GetCamera()->GetY() -= dt * m_CameraSpeed;
		}
		if (Orange::Input::Keyboard(ORANGE_KEY_UP))
		{
			Orange::App::GetCamera()->GetY() += dt * m_CameraSpeed;
		}
	}

	virtual void OnEvent(const Orange::Event& e) override
	{
		if (e.GetType() == Orange::EventType::Wheel)
		{
			auto& ev = e.Cast<Orange::WheelEvent>();
			if (ev.GetValue() < 0.0f && m_CameraWidth > 1.0f)
				m_CameraWidth += ev.GetValue() / 5.0f;
			if (ev.GetValue() > 0.0f && m_CameraWidth < 20.0f)
				m_CameraWidth += ev.GetValue() / 5.0f;
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
	float m_CameraSpeed = 5.0f;
	float m_CameraWidth = 10.0f;

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