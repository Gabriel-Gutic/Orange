#include "pch.h"
#include "ComponentTests.h"


namespace OrangeEditor
{
	ComponentTestsLayer::ComponentTestsLayer()
	{
		Orange::ImGuiDevice::ShowDockspace();

		m_FrameBuffer = std::make_shared<Orange::FrameBuffer>();
		Orange::App::GetCamera()->SetFrameBuffer(m_FrameBuffer);

		Orange::App::GetWindow()->SetVSync(true);

		// Tests

		PRINT("EmplaceComponent Test");
		Orange::App::GetCamera()->EmplaceComponent<Orange::Rigidbody>();
		CHECK_TEST(Orange::App::GetCamera()->GetAllComponents().size() == 1);

		PRINT("AddComponent Test");
		Orange::Rigidbody comp = {};
		Orange::App::GetCamera()->AddComponent<Orange::Rigidbody>(comp);
		CHECK_TEST(Orange::App::GetCamera()->GetAllComponents().size() == 2);

		PRINT("RemoveComponent Test");
		Orange::App::GetCamera()->RemoveComponent<Orange::Rigidbody>();
		CHECK_TEST(Orange::App::GetCamera()->GetAllComponents().size() == 1);

		PRINT("GetComponent Test");
		Orange::App::GetCamera()->GetComponent<Orange::Rigidbody>();
		// Orange::App::GetCamera()->RemoveComponent<Orange::Rigidbody>();
		// Orange::App::GetCamera()->GetComponent<Orange::Rigidbody>();
	}

	void ComponentTestsLayer::OnUpdate(float dt)
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

	void ComponentTestsLayer::OnEvent(const Orange::Event& e)
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

	void ComponentTestsLayer::OnImGui()
	{
		ImGui::ShowDemoWindow((bool*)0);

		Orange::ImGuiDevice::RenderWindow("SceneView", m_FrameBuffer);

		ImGui::Begin("Scene");

		Orange::App::GetScene()->ToImGuiTree();

		ImGui::End();
	}
}