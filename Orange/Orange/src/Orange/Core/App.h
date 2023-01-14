#pragma once
#include "Event/Events.h"
#include "Orange/Renderer/Camera.h"
#include "Window.h"
#include "Layer.h"


namespace Orange
{
	class App
	{
	public:
		App();
		virtual ~App();

		void Run();
		void Exit();

		static std::unique_ptr<Window>& GetWindow();
		static std::unique_ptr<Camera>& GetCamera() { return s_Instance->m_Camera; }

		static App* Create();

		static void PushEvent(Event* e);
		static void PopEvent();
		static void PushLayer(Layer* layer);
		static void PopLayer();
	private:
		bool m_IsRunning;
		std::queue<Event*> m_EventQueue;
		std::vector<Layer*> m_LayerStack;

		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Window> m_Window;

		static App* s_Instance;
	};
}
