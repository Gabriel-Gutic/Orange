#pragma once
#include "Window.h"
#include "Layer.h"
#include "Event/Events.h"

#include "Objects/Camera.h"
#include "Objects/Scene.h"


namespace Orange
{
	class App
	{
	public:
		App();
		virtual ~App();

		static void Main(int argc, char** args);

		void Run();
		void Exit();

		static std::unique_ptr<Window>& GetWindow();
		static std::shared_ptr<Camera>& GetCamera() { return s_Instance->m_Camera; }
		static std::shared_ptr<Scene>& GetScene() { return s_Instance->m_Scene; }
		static size_t GetFPS();
		static float GetDeltaTime();

		static App* Create();

		static void PushEvent(Event* e);
		static void PopEvent();
		static void PushLayer(Layer* layer);
		static void PopLayer();
	private:
		Timer m_Timer;
		size_t m_FPS;
		size_t m_FrameCounter;
		float m_DeltaTime;

		bool m_IsRunning;
		std::queue<Event*> m_EventQueue;
		std::vector<Layer*> m_LayerStack;

		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<Camera> m_Camera;
		std::unique_ptr<Window> m_Window;

		static App* s_Instance;
	};
}
