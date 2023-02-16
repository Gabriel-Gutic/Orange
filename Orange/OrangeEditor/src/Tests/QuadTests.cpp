#include "pch.h"
#include "QuadTests.h"

#include "Tests.h"


namespace OrangeEditor
{
	QuadTestsLayer::QuadTestsLayer()
	{
		Orange::ImGuiDevice::ShowDockspace();

		Orange::App::GetCamera()->SetFrameBuffer(std::make_shared<Orange::FrameBuffer>());
		std::dynamic_pointer_cast<Orange::Camera>(Orange::App::GetScene()->GetChildren()[0])->SetFrameBuffer(std::make_shared<Orange::FrameBuffer>());

		Orange::App::GetWindow()->SetVSync(true);

		auto camera = std::dynamic_pointer_cast<Orange::Camera>(Orange::App::GetScene()->GetChildren()[0]);
		Orange::Renderer::AddCamera(camera);
		camera->SetWidth(m_CameraWidth);

		// Tests
		auto firstQuad = Orange::CreateQuad();
		Orange::App::GetScene()->PushChild(firstQuad);
	}

	void QuadTestsLayer::OnUpdate(float dt)
	{
		if (Orange::Input::Keyboard(ORANGE_KEY_F))
		{
			PRINT("FPS: {0}", Orange::App::GetFPS());
		}

		Orange::App::GetCamera()->SetWidth(m_CameraWidth);

		if (Orange::Input::Keyboard(ORANGE_KEY_LEFT))
		{
			Orange::App::GetCamera()->GetTransform().Position.x -= dt * m_CameraSpeed;
		}
		if (Orange::Input::Keyboard(ORANGE_KEY_RIGHT))
		{
			Orange::App::GetCamera()->GetTransform().Position.x += dt * m_CameraSpeed;
		}
		if (Orange::Input::Keyboard(ORANGE_KEY_DOWN))
		{
			Orange::App::GetCamera()->GetTransform().Position.y -= dt * m_CameraSpeed;
		}
		if (Orange::Input::Keyboard(ORANGE_KEY_UP))
		{
			Orange::App::GetCamera()->GetTransform().Position.y += dt * m_CameraSpeed;
		}
	}

	void QuadTestsLayer::OnEvent(const Orange::Event& e)
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

	void QuadTestsLayer::OnImGui()
	{
		ImGui::ShowDemoWindow((bool*)0);

		Orange::ImGuiDevice::RenderWindow("SceneView", Orange::App::GetCamera()->GetFrameBuffer());
		Orange::ImGuiDevice::RenderWindow("Game", 
			std::dynamic_pointer_cast<Orange::Camera>(Orange::App::GetScene()->GetChildren()[0])->GetFrameBuffer());

		ImGui::Begin("SceneTree");
		Orange::App::GetScene()->ToImGuiTree();
		ImGui::End();


		ImGui::Begin("Inspector");
		Orange::App::GetScene()->ShowSelectedItem();
		ImGui::End();
	}
}