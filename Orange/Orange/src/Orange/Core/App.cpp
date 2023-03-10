#include "pchOrange.h"
#include "App.h"

#include "Renderer/Renderer.h"
#include "ImGuiDevice.h"
#include "Math/RandomEngine.h"


namespace Orange
{
	App* App::s_Instance = nullptr;
	App::App()
		:m_IsRunning(true), m_FPS(60),
		m_FrameCounter(0), m_DeltaTime(1.0f / 60.0f)
	{
		ORANGE_ASSERT(!s_Instance, "App already initialized!");
		s_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Camera = std::make_unique<Camera>();
		m_Scene = std::make_shared<Scene>();

		Renderer::Initialize();

		Renderer::AddCamera(m_Camera);

		ImGuiDevice::Initialize();
	}

	App::~App()
	{
		for (auto& layer : m_LayerStack)
			delete layer;
		m_LayerStack.clear();

		ImGuiDevice::Terminate();

		Renderer::Terminate();
	}

	void App::Main(int argc, char** args)
	{
		Orange::Logger::Initialize();

		Orange::RandomEngine::Initialize();

		auto* app = App::Create();

		app->Run();

		delete app;

		Orange::RandomEngine::Terminate();
	}

	void App::Run()
	{
		m_Timer.Restart();

		while (m_IsRunning)
		{
			if (m_Timer.GetSeconds() >= 1.0f)
			{
				m_FPS = m_FrameCounter;
				m_FrameCounter = 0;
				m_DeltaTime = 1.0f / static_cast<float>(m_FPS);
				m_Timer.Restart();
			}

			while (!m_EventQueue.empty())
			{
				Event& e = *m_EventQueue.front();
				
				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				ORANGE_PRINT(e.ToString());

				for (auto& layer : m_LayerStack)
					layer->OnEvent(e);

				PopEvent();
			}

			Renderer::Begin();

			for (auto& layer : m_LayerStack)
				layer->OnUpdate(m_DeltaTime);

			m_Scene->Draw();

			Renderer::End();
			
			ImGuiDevice::Begin();

			for (auto& layer : m_LayerStack)
				layer->OnImGui();

			ImGuiDevice::End();

			m_Window->SwapBuffers();

			m_FrameCounter++;
		}
	}

	void App::Exit()
	{
		m_IsRunning = false;
	}

	std::unique_ptr<Window>& App::GetWindow()
	{
		return s_Instance->m_Window;
	}

	size_t App::GetFPS()
	{
		return s_Instance->m_FPS;
	}

	float App::GetDeltaTime()
	{
		return s_Instance->m_DeltaTime;
	}

	void App::PushEvent(Event* e)
	{
		s_Instance->m_EventQueue.push(e);
	}

	void App::PopEvent()
	{
		delete s_Instance->m_EventQueue.front();
		s_Instance->m_EventQueue.pop();
	}

	void App::PushLayer(Layer* layer)
	{
		if (layer)
		{
			s_Instance->m_LayerStack.push_back(layer);
		}
	}

	void App::PopLayer()
	{
		if (!s_Instance->m_LayerStack.empty())
		{
			delete s_Instance->m_LayerStack.back();
			s_Instance->m_LayerStack.pop_back();
		}
	}
}

