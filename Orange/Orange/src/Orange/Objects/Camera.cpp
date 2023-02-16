#include "pchOrange.h"
#include "Camera.h"

#include "Core/App.h"


namespace Orange
{
	Camera::Camera()
		:GameObject("Camera"), m_FrameBuffer(nullptr), m_Size()
	{
	}

	Mat3 Camera::GetProjectionView(bool flippedVertically) const
	{
		float w, h;
		if (m_Size.x != 0.0f)
			w = m_Size.x;
		else
			w = App::GetWindow()->GetWidth();

		if (m_Size.y != 0.0f)
			h = m_Size.y;
		else
			h = w / App::GetWindow()->GetAspectRatio();

		float l = m_Transform.Position.x - w / 2.0f;
		float r = m_Transform.Position.x + w / 2.0f;
		float b = m_Transform.Position.y - h / 2.0f;
		float t = m_Transform.Position.y + h / 2.0f;

		Mat3 M(1.0f);
		M[0][0] = 2 / (r - l);
		M[1][1] = 2 / (t - b);
		M[0][2] = (-r - l) / (r - l);
		M[1][2] = (-t - b) / (t - b);

		Mat3 R = Math::Rotate(-m_Transform.Rotation);


		if (flippedVertically)
			M[1][1] *= -1;
		M = M * R;

		return M;
	}

	void Camera::SetWidth(float width)
	{
		m_Size.x = width;
	}

	void Camera::SetHeight(float height)
	{
		m_Size.y = height;
	}

	void Camera::SetFrameBuffer(const std::shared_ptr<FrameBuffer>& frameBuffer)
	{
		m_FrameBuffer = frameBuffer;
	}

	const std::shared_ptr<FrameBuffer>& Camera::GetFrameBuffer() const
	{
		return m_FrameBuffer;
	}
}