#include "pchOrange.h"
#include "Input.h"

#include "Core/App.h"
#include "Core/ImGuiDevice.h"
#include "Renderer/Renderer.h"
#include "KeyboardCodes.h"

#include <GLFW/glfw3.h>


namespace Orange
{
	bool Input::Keyboard(int key)
	{
		bool status = static_cast<bool>(glfwGetKey(std::any_cast<GLFWwindow*>(App::GetWindow()->Get()), key));
		return status;
	}

	bool Input::Mouse(int button)
	{
		return glfwGetMouseButton(std::any_cast<GLFWwindow*>(App::GetWindow()->Get()), button);
	}

	//Float2 Input::MousePos(const std::shared_ptr<Camera>& camera)
	//{
	//	if (camera->GetFrameBuffer())
	//	{
	//		// Coordinates inside ImGui RenderWindow
	//		return ImGuiDevice::RenderWindowMousePos();
	//	}
	//	else
	//	{
	//		// Coordinates inside entire window
	//		Float2 pos;
	//		double px, py;

	//		auto& window = App::GetWindow();
	//		glfwGetCursorPos(std::any_cast<GLFWwindow*>(window->Get()),
	//			&px, &py);
	//		pos.x = static_cast<float>(px);
	//		pos.y = static_cast<float>(py);
	//		pos.y = -(pos.y - window->GetHeight());

	//		return pos;
	//	}
	//}

	//Float2 Input::MouseToWorldCoords(const std::shared_ptr<Camera>& camera)
	//{
	//	auto [x, y] = MousePos().data;
	//	auto [w, h] = ScreenSize().data;

	//	Float2 pos;

	//	pos.x = x / w * 2.0f - 1.0f;
	//	pos.y = y / h * 2.0f - 1.0f;

	//	pos = camera->GetProjectionView().Inverse() * pos;

	//	return pos;
	//}

	//float Input::MouseX()
	//{
	//	return MousePos().x;
	//}

	//float Input::MouseY()
	//{
	//	return MousePos().y;
	//}

	//Float2 Input::ScreenSize()
	//{
	//	if (Renderer::GetFrameBuffer())
	//	{
	//		// Size of the ImGui RenderWindow screen
	//		return ImGuiDevice::RenderWindowSize();
	//	}
	//	else
	//	{
	//		// Size of the entire screen
	//		auto [w, h] = App::GetWindow()->GetSize().data;
	//		return Float2(w, h);
	//	}
	//}

	//float Input::ScreenWidth()
	//{
	//	return ScreenSize().x;
	//}

	//float Input::ScreenHeight()
	//{
	//	return ScreenSize().y;
	//}
}


