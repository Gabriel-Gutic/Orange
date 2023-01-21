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
	private:
		static ImGuiDevice* s_Instance;
	};
}