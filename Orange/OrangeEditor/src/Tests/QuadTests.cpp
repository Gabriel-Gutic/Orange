#include "pch.h"
#include "QuadTests.h"

#include "Tests.h"


namespace OrangeEditor
{
	QuadTestsLayer::QuadTestsLayer()
	{
		Orange::ImGuiDevice::ShowDockspace();

		m_FrameBuffer = std::make_shared<Orange::FrameBuffer>();
		Orange::Renderer::SetFrameBuffer(m_FrameBuffer);

		Orange::App::GetWindow()->SetVSync(true);

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

		Orange::ImGuiDevice::RenderWindow("SceneView", m_FrameBuffer);

		ImGui::Begin("SceneTree");
		Orange::App::GetScene()->ToImGuiTree();
		ImGui::End();


		ImGui::Begin("Inspector");
		Orange::App::GetScene()->ShowSelectedItem();
		ImGui::End();
	}
}