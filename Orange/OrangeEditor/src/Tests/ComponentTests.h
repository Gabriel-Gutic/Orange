#pragma once
#include "Tests.h"


namespace OrangeEditor
{
	class ComponentTestsLayer : public Orange::Layer
	{
	public:
		ComponentTestsLayer();
		~ComponentTestsLayer() = default;

		virtual void OnUpdate(float dt) override;
		virtual void OnEvent(const Orange::Event& e) override;
		virtual void OnImGui() override;
	private:
		float m_CameraSpeed = 5.0f;
		float m_CameraWidth = 10.0f;

		std::shared_ptr<Orange::FrameBuffer> m_FrameBuffer;
	private:
	};
}
