#include "pchOrange.h"
#include "App.h"

#include "Renderer/Renderer.h"


namespace Orange
{
	App* App::s_Instance = nullptr;
	App::App()
		:m_IsRunning(true)
	{
		ORANGE_ASSERT(!s_Instance, "App already initialized!");
		s_Instance = this;

		m_Window = std::make_unique<Window>();

		Renderer::Initialize();
	}

	App::~App()
	{
		Renderer::Terminate();
	}

	void App::Run()
	{
		while (m_IsRunning)
		{
			m_Window->Clear(Color::Blue);

			while (!m_EventQueue.empty())
			{
				Event& e = *m_EventQueue.front();
				
				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				ORANGE_PRINT(e.ToString());

				PopEvent();
			}

			Renderer::Begin();

			Renderer::End();

			m_Window->SwapBuffers();
		}
	}

	void App::Exit()
	{
		m_IsRunning = false;
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
}

