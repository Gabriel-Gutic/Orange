#include "pch.h"


/*
class TextureTests : public Orange::Layer
{
public:
	TextureTests()
	{
		Orange::ImGuiDevice::ShowDockspace();

		m_FrameBuffer = std::make_shared<Orange::FrameBuffer>();
		Orange::Renderer::SetFrameBuffer(m_FrameBuffer);

		// Test 1:
		PRINT("Load textures with auto-name");

		Orange::Resources::Textures::Load("Assets/Images/1.jpg");
		Orange::Resources::Textures::Load("Assets/Images/1.jpg");
		Orange::Resources::Textures::Load("Assets/Images/1.jpg");
		Orange::Resources::Textures::Load("Assets/Images/1.jpg");

		for (auto& [name, texture] : Orange::Resources::Textures::GetAll())
		{
			PRINT("Texture: '{0}' with filepath '{1}'", name, texture->GetFilepath());
		}

		// Test 2:
		PRINT("Load textures by specifying name");

		Orange::Resources::Textures::Load("Assets/Images/1.jpg", "Image");
		Orange::Resources::Textures::Load("Assets/Images/dragon.png", "Image");
		Orange::Resources::Textures::Load("Assets/Images/tileset.png", "Image");

		for (auto& [name, texture] : Orange::Resources::Textures::GetAll())
		{
			PRINT("Texture: '{0}' with filepath '{1}'", name, texture->GetFilepath());
		}

		// Test 3:
		PRINT("Add premade textures");

		auto texture1 = Orange::Texture::CreateShared("Assets/Images/1.jpg");
		auto texture2 = Orange::Texture::CreateShared("Assets/Images/1.jpg");

		Orange::Resources::Textures::Add(texture1, "AddTexture1");
		Orange::Resources::Textures::Add(texture2, "AddTexture2");

		for (auto& [name, texture] : Orange::Resources::Textures::GetAll())
		{
			PRINT("Texture: '{0}' with filepath '{1}'", name, texture->GetFilepath());
		}

		// Test 4:
		PRINT("Unload textures");

		Orange::Resources::Textures::Unload("AddTexture1");
		Orange::Resources::Textures::Unload("AddTexture2");

		for (auto& [name, texture] : Orange::Resources::Textures::GetAll())
		{
			PRINT("Texture: '{0}' with filepath '{1}'", name, texture->GetFilepath());
		}
	}

	~TextureTests()
	{

	}

	virtual void OnUpdate(float dt) override
	{
		if (Orange::Input::Keyboard(ORANGE_KEY_F))
		{
			PRINT("FPS: {0}", Orange::App::GetFPS());
		}

		Orange::App::GetCamera()->SetWidth(m_CameraWidth);

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

	std::shared_ptr<Orange::FrameBuffer> m_FrameBuffer;
};


class TileApp : public Orange::App
{
public:
	TileApp()
	{
		PushLayer(new TextureTests());
	}
};


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<TileApp>();
}

*/