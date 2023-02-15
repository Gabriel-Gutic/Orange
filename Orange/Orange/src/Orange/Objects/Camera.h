#pragma once
#include "GameObject.h"
#include "Renderer/FrameBuffer.h"


namespace Orange
{
	class Camera : public GameObject
	{
	public:
		Camera();
		~Camera() = default;

		Mat3 GetProjectionView(bool flippedVertically = false) const;

		void SetWidth(float width);
		void SetHeight(float height);
	private:
		Float2 m_Size;
	};
}
