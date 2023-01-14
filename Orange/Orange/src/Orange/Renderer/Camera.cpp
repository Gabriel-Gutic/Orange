#include "pchOrange.h"
#include "Camera.h"

#include "Core/App.h"


namespace Orange
{
	Camera::Camera()
		:m_Position(), m_Size()
	{
	}

	Mat3 Camera::GetProjectionView() const
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

		float l = m_Position.x - w / 2.0f;
		float r = m_Position.x + w / 2.0f;
		float b = m_Position.y - h / 2.0f;
		float t = m_Position.y + h / 2.0f;

		Mat3 M(1.0f);
		M[0][0] = 2 / (r - l);
		M[1][1] = 2 / (t - b);
		M[0][2] = (-r - l) / (r - l);
		M[1][2] = (-t - b) / (t - b);

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

	void Camera::SetX(float x)
	{
		m_Position.x = x;
	}

	void Camera::SetY(float y)
	{
		m_Position.y = y;
	}

	void Camera::SetPosition(const Float2& pos)
	{
		m_Position = pos;
	}

	float& Camera::GetX()
	{
		return m_Position.x;
	}

	float& Camera::GetY()
	{
		return m_Position.y;
	}

	Float2& Camera::GetPosition()
	{
		return m_Position;
	}

	const float& Camera::GetX() const
	{
		return m_Position.x;
	}

	const float& Camera::GetY() const
	{
		return m_Position.y;
	}

	const Float2& Camera::GetPosition() const
	{
		return m_Position;
	}
}