#pragma once
#include "Renderer/FrameBuffer.h"


namespace Orange
{
	class ImGuiDevice
	{
	private:
		ImGuiDevice();
	public:
		ImGuiDevice(const ImGuiDevice&) = delete;
		~ImGuiDevice();

		static void Initialize();
		static void Terminate();

		static void Begin();
		static void End();

		static void ShowDockspace();
		static void HideDockspace();
		static void Dockspace();

		static void RenderWindow(std::string_view name, const std::shared_ptr<FrameBuffer>& fb, bool centered = false);
		static Float2 RenderWindowMousePos();
		static Float2 RenderWindowSize();
	private:
		void SetDarkThemeColors();
	private:
		bool m_IsDockspaceShown;
		Float2 m_RenderWindowMousePos;
		Float2 m_RenderWindowSize;
		
		static ImGuiDevice* s_Instance;
	};
}