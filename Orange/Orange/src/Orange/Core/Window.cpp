#include "pchOrange.h"
#include "Window.h"

#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Orange
{
	void GLAPIENTRY
		ErrorCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		ORANGE_ERROR(message);
	}

	Window::Window(std::string_view title, int width, int height)
		:m_Data({
			title.data(),
			width, height,
			100, 100,
			false,
			false
			})
	{
		/* Initialize the library */
		ORANGE_ASSERT(glfwInit(), "Failed to initialize GLFW!");

		/* Create a windowed mode window and its OpenGL context */
		auto window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			ORANGE_ASSERT(0, "Failed to create GLFW Window!");
		}

		glfwSetWindowPos(window, m_Data.X, m_Data.Y);

		m_Handle = window;

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Initialize Glad */
		ORANGE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(ErrorCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glfwSwapInterval(m_Data.VSync);
		glfwSetWindowUserPointer(window, &m_Data);

		//SetIcon("assets/Logo/logo.ico");

		// Check if CapsLock and NumLock are on
		// glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action)
			{
			case GLFW_PRESS:
				App::PushEvent(new KeyPressEvent(key));
				break;
			case GLFW_RELEASE:
				App::PushEvent(new KeyReleaseEvent(key));
				break;
			case GLFW_REPEAT:
				App::PushEvent(new KeyRepeatEvent(key));
				break;
			}
			});

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
			App::PushEvent(new CharEvent(codepoint));
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			switch (action)
			{
			case GLFW_PRESS:
				App::PushEvent(new MouseButtonPressEvent(button));
				break;
			case GLFW_RELEASE:
				App::PushEvent(new MouseButtonReleaseEvent(button));
				break;
			}
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			App::PushEvent(new MouseMoveEvent(static_cast<float>(xpos), static_cast<float>(ypos)));
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			App::PushEvent(new WheelEvent(static_cast<float>(yoffset)));
			});

		glfwSetWindowPosCallback(window, [](GLFWwindow* window, int xpos, int ypos) {
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			data.X = xpos;
			data.Y = ypos;
			});

		glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized) {
			App::PushEvent(new WindowMaximizeEvent(maximized));
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {

			auto& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			data.Width = width;
			data.Height = height;

			glViewport(0, 0, data.Width, data.Height);

			if (data.Width == 0 || data.Height == 0)
				App::PushEvent(new WindowMinimizeEvent(true));
			else App::PushEvent(new WindowMinimizeEvent(false));

			App::PushEvent(new WindowResizeEvent(width, height));
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			App::PushEvent(new WindowCloseEvent());
			});
	}

	Window::~Window()
	{
		glfwDestroyWindow(std::any_cast<GLFWwindow*>(m_Handle));
		glfwTerminate();
	}

	std::any Window::Get()
	{
		return m_Handle;
	}

	void Window::Clear(const FColor& color) const
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Window::SwapBuffers() const
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(std::any_cast<GLFWwindow*>(m_Handle));

		/* Poll for and process events */
		glfwPollEvents();
	}

	int Window::GetWidth() const
	{
		return m_Data.Width;
	}

	int Window::GetHeight() const
	{
		return m_Data.Height;
	}

	Int2 Window::GetSize() const
	{
		return Int2(m_Data.Width, m_Data.Height);
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(std::any_cast<GLFWwindow*>(m_Handle), width, height);
		m_Data.Width = width;
		m_Data.Height = height;
	}

	void Window::SetWidth(int width)
	{
		SetSize(width, m_Data.Height);
	}

	void Window::SetHeight(int height)
	{
		SetSize(m_Data.Width, height);
	}

	float Window::GetAspectRatio() const
	{
		return static_cast<float>(m_Data.Width) / static_cast<float>(m_Data.Height);
	}

	int Window::GetX() const
	{
		return m_Data.X;
	}

	int Window::GetY() const
	{
		return m_Data.Y;
	}

	Int2 Window::GetPos() const
	{
		return Int2(m_Data.X, m_Data.Y);
	}

	void Window::SetPos(int x, int y)
	{
		m_Data.X = x;
		m_Data.Y = y;
		glfwSetWindowPos(std::any_cast<GLFWwindow*>(m_Handle), x, y);
	}

	void Window::SetX(int x)
	{
		SetPos(x, m_Data.Y);
	}

	void Window::SetY(int y)
	{
		SetPos(m_Data.X, y);
	}

	void Window::SetTitle(std::string_view title)
	{
		glfwSetWindowTitle(std::any_cast<GLFWwindow*>(m_Handle), title.data());
		m_Data.Title = title;
	}

	const std::string& Window::GetTitle() const
	{
		return m_Data.Title;
	}

	void Window::SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		m_Data.VSync = vsync;
	}

	bool Window::GetVSync() const
	{
		return m_Data.VSync;
	}

	void Window::SetFullscreen(bool fullscreen)
	{
		m_Data.Fullscreen = fullscreen;

		auto window = std::any_cast<GLFWwindow*>(m_Handle);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (fullscreen)
		{
			// Go in fullscreen mode
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			// Go in windowed mode
			glfwSetWindowMonitor(window, NULL, 200, 200, 1280, 720, 0);
		}
	}

	bool Window::IsFullscreen() const
	{
		return m_Data.Fullscreen;
	}

	//void Window::SetIcon(std::string_view iconPath)
	//{
	//	if (std::filesystem::exists(iconPath.data()))
	//	{
	//		if (iconPath.substr(iconPath.length() - 4) == ".ico")
	//		{
	//			GLFWimage images[1];
	//			images[0].pixels = stbi_load(iconPath.data(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
	//			glfwSetWindowIcon(std::any_cast<GLFWwindow*>(m_Window), 1, images);
	//			stbi_image_free(images[0].pixels);
	//		}
	//		else
	//		{
	//			TOMATO_ERROR("Not a valid .ico file: '{0}'!", iconPath.data());
	//		}
	//	}
	//	else
	//	{
	//		TOMATO_ERROR("Icon '{0}' not found!", iconPath.data());
	//	}
	//}
}