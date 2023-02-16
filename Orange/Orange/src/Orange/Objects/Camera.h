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

		void SetFrameBuffer(const std::shared_ptr<FrameBuffer>& frameBuffer);
		const std::shared_ptr<FrameBuffer>& GetFrameBuffer() const;
	private:
		Float2 m_Size;
		std::shared_ptr<FrameBuffer> m_FrameBuffer;
	};
}
