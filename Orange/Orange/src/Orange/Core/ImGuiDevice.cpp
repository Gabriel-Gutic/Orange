#include "pchOrange.h"
#include "ImGuiDevice.h"

#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>


namespace Orange
{
	ImGuiDevice* ImGuiDevice::s_Instance = nullptr;
	ImGuiDevice::ImGuiDevice()
		:m_IsDockspaceShown(false), 
		m_RenderWindowMousePos({ 0.0f, 0.0f }),
		m_RenderWindowSize({ 0.0f, 0.0f })
	{
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        const char* fontPath = "Assets/Fonts/Roboto/Roboto-Regular.ttf";
        io.Fonts->AddFontFromFileTTF(fontPath, 16.0f);

        // Setup Platform/Renderer bindings
        auto window = std::any_cast<GLFWwindow*>(App::GetWindow()->Get());

        ORANGE_ASSERT(ImGui_ImplGlfw_InitForOpenGL(window, true), "Failed to configure ImGui for GLFW!");
        ORANGE_ASSERT(ImGui_ImplOpenGL3_Init(), "Failed to initialize OpenGL3 for ImGui!");

        // Setup Dear ImGui style
        SetDarkThemeColors();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        style.WindowBorderSize = 0.0f;
	}

	ImGuiDevice::~ImGuiDevice()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiDevice::Initialize()
	{
		ORANGE_ASSERT(!s_Instance, "ImGui allready initialized!");
		s_Instance = new ImGuiDevice();
	}

	void ImGuiDevice::Terminate()
	{
		delete s_Instance;
	}

	void ImGuiDevice::Begin()
	{
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (s_Instance->m_IsDockspaceShown)
		{
			Dockspace();
		}
	}

	void ImGuiDevice::End()
	{
		auto& window = App::GetWindow();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiDevice::ShowDockspace()
	{
		s_Instance->m_IsDockspaceShown = true;
	}

	void ImGuiDevice::HideDockspace()
	{
		s_Instance->m_IsDockspaceShown = false;
	}

	void ImGuiDevice::Dockspace()
	{
		auto& window = App::GetWindow();

		ImGui::SetNextWindowPos(ImVec2(window->GetX(), window->GetY()));
		ImGui::SetNextWindowSize(ImVec2(window->GetWidth(), window->GetHeight()));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", NULL,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse
		);
		ImGui::PopStyleVar();

		// Declare Central dockspace
		auto dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);

		ImGui::End();
	}

	void ImGuiDevice::RenderWindow(const std::shared_ptr<FrameBuffer>& fb, bool centered)
	{
		if (fb)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("RenderWindow");

			auto [w, h] = fb->GetSize().data;
			ImVec2 size = ImGui::GetWindowSize();

			void* id = (void*)fb->GetTexture()->GetID();
			float height = (size.x * h) / (float)w;

			if (centered)
			{
				float space = (size.y - height) / 2.0f;
				ImGui::SetCursorPos(ImVec2(0.0f, space));
			}

			s_Instance->m_RenderWindowMousePos = Float2(
				ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x,
				-static_cast<int>(ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y - height)
			);

			ImGui::Image((ImTextureID)id, ImVec2(size.x, height));

			s_Instance->m_RenderWindowSize = Float2(
				size.x,
				height
			);

			ImGui::End();
			ImGui::PopStyleVar();
		}
		else
			ORANGE_ERROR("Invalid FrameBuffer!");
	}

	Float2 ImGuiDevice::RenderWindowMousePos()
	{
		return s_Instance->m_RenderWindowMousePos;
	}

	Float2 ImGuiDevice::RenderWindowSize()
	{
		return s_Instance->m_RenderWindowSize;
	}

    void ImGuiDevice::SetDarkThemeColors()
    {
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    }
}