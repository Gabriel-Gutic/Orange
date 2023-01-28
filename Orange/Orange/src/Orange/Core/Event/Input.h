#pragma once
#include "Renderer/Camera.h"


namespace Orange::Input
{
	bool Keyboard(int key);
	bool Mouse(int button);
	Float2 MousePos();
	Float2 MouseToWorldCoords(const std::shared_ptr<Camera>& camera);
	float MouseX();
	float MouseY();
	Float2 ScreenSize();
	float ScreenWidth();
	float ScreenHeight();
}
