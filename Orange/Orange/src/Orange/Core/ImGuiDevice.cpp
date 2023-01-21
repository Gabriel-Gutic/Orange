#include "pchOrange.h"
#include "ImGuiDevice.h"


namespace Orange
{
	ImGuiDevice* ImGuiDevice::s_Instance = nullptr;
	ImGuiDevice::ImGuiDevice()
	{
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        const char* fontPath = "assets/Fonts/Roboto/Roboto-Regular.ttf";
        io.Fonts->AddFontFromFileTTF(fontPath, 16.0f);

        // Setup Platform/Renderer bindings
        s_GUI_API->Initialize();

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
}