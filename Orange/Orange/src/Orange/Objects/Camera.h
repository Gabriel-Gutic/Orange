#pragma once
#include "GameObject.h"


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

		void SetX(float x);
		void SetY(float y);
		void SetPosition(const Float2& pos);

		float& GetX();
		float& GetY();
		Float2& GetPosition();

		const float& GetX() const;
		const float& GetY() const;
		const Float2& GetPosition() const;
	private:
		Float2 m_Position;
		Float2 m_Size;
	};
}
