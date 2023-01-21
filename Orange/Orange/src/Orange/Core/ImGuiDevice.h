#pragma once


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
	private:
		void SetDarkThemeColors();
	private:
		bool m_IsDockspaceShown;
		
		static ImGuiDevice* s_Instance;
	};
}