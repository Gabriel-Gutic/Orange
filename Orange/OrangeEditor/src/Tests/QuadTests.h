#pragma once


namespace OrangeEditor
{
	class QuadTestsLayer : public Orange::Layer
	{
	public:
		QuadTestsLayer();
		~QuadTestsLayer() = default;

		virtual void OnUpdate(float dt) override;
		virtual void OnEvent(const Orange::Event& e) override;
		virtual void OnImGui() override;
	private:
		float m_CameraSpeed = 5.0f;
		float m_CameraWidth = 10.0f;
	};
}