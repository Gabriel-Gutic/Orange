#include "pch.h"

#include "Tests/ComponentTests.h"
#include "Tests/QuadTests.h"


namespace OrangeEditor
{
	class OrangeEditorLayer : public Orange::Layer
	{
	public:
		OrangeEditorLayer()
		{
			Orange::ImGuiDevice::ShowDockspace();

			m_FrameBuffer = std::make_shared<Orange::FrameBuffer>();
			Orange::App::GetCamera()->SetFrameBuffer(m_FrameBuffer);

			Orange::App::GetWindow()->SetVSync(true);


			Orange::App::GetCamera()->EmplaceComponent<Orange::Rigidbody>();
		}

		~OrangeEditorLayer()
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

			Orange::ImGuiDevice::RenderWindow("SceneView", m_FrameBuffer);

			ImGui::Begin("Scene");

			Orange::App::GetScene()->ToImGuiTree();

			ImGui::End();
		}
	private:
		float m_CameraSpeed = 5.0f;
		float m_CameraWidth = 10.0f;

		std::shared_ptr<Orange::FrameBuffer> m_FrameBuffer;
	};


	class OrangeEditor : public Orange::App
	{
	public:
		OrangeEditor()
		{
			PushLayer(new QuadTestsLayer());
		}
	};
}


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<OrangeEditor::OrangeEditor>();
}