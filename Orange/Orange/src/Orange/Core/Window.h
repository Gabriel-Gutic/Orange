#pragma once


namespace Orange
{
	struct WindowData
	{
		std::string Title;
		int Width, Height;
		int X, Y;
		bool VSync;
		bool Fullscreen;
	};

	class Window
	{
	public:
		Window(std::string_view title = "Orange", int width = 1280, int height = 720);
		virtual ~Window();

		std::any Get();

		// TODO: Add background color
		void Clear(const Color& color) const;
		void SwapBuffers() const;

		int GetWidth() const;
		int GetHeight() const;
		Int2 GetSize() const;
		void SetSize(int width, int height);
		void SetWidth(int width);
		void SetHeight(int height);
		float GetAspectRatio() const;

		int GetX() const;
		int GetY() const;
		Int2 GetPos() const;
		void SetPos(int x, int y);
		void SetX(int x);
		void SetY(int y);

		void SetTitle(std::string_view title);
		const std::string& GetTitle() const;
		//void SetIcon(std::string_view iconPath);

		void SetVSync(bool vsync);
		bool GetVSync() const;

		void SetFullscreen(bool fullscreen);
		bool IsFullscreen() const;
	private:
		std::any m_Handle;
		WindowData m_Data;
	};
}
