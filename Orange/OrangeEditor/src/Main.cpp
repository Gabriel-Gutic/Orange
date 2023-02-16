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

			std::dynamic_pointer_cast<Orange::Camera>(Orange::App::GetScene()->GetChildren()[0])->SetFrameBuffer(std::make_shared<Orange::FrameBuffer>());
			auto camera = std::dynamic_pointer_cast<Orange::Camera>(Orange::App::GetScene()->GetChildren()[0]);
			Orange::Renderer::AddCamera(camera);
			camera->SetWidth(m_CameraWidth);

			Orange::App::GetScene()->PushChild(Orange::CreateQuad());
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

			Orange::ImGuiDevice::RenderWindow("Game",
				std::dynamic_pointer_cast<Orange::Camera>(Orange::App::GetScene()->GetChildren()[0])->GetFrameBuffer());
			Orange::ImGuiDevice::RenderWindow("SceneView", Orange::App::GetCamera()->GetFrameBuffer());

			ImGui::Begin("SceneTree");
			Orange::App::GetScene()->ToImGuiTree();
			ImGui::End();


			ImGui::Begin("Inspector");
			Orange::App::GetScene()->ShowSelectedItem();
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
			PushLayer(new OrangeEditorLayer());
		}
	};
}


Orange::App* Orange::App::Create()
{
	return Orange::Alloc<OrangeEditor::OrangeEditor>();
}