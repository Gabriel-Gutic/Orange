#include "pchOrange.h"
#include "App.h"

#include "Renderer/Renderer.h"
#include "ImGuiDevice.h"


namespace Orange
{
	App* App::s_Instance = nullptr;
	App::App()
		:m_IsRunning(true)
	{
		ORANGE_ASSERT(!s_Instance, "App already initialized!");
		s_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Camera = std::make_unique<Camera>();
		m_Scene = std::make_shared<Scene>();

		Renderer::Initialize();

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

	void App::Run()
	{
		while (m_IsRunning)
		{
			while (!m_EventQueue.empty())
			{
				Event& e = *m_EventQueue.front();
				
				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				//ORANGE_PRINT(e.ToString());

				for (auto& layer : m_LayerStack)
					layer->OnEvent(e);

				PopEvent();
			}

			Renderer::Begin();

			m_Window->Clear(FColor::Blue);

			for (auto& layer : m_LayerStack)
				layer->OnUpdate();

			m_Scene->Draw();

			Renderer::End();
			
			ImGuiDevice::Begin();

			for (auto& layer : m_LayerStack)
				layer->OnImGui();

			ImGuiDevice::End();


			m_Window->SwapBuffers();
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

