#pragma once


namespace Orange
{
	struct Transform
	{
		Float2 Position;
		Float2 Scale;
		float Rotation;

		Transform(const Float2& position = Float2(), const Float2& scale = Float2(), float rotation = 0.0f);
		Mat3 ToMat3() const;
	};
}