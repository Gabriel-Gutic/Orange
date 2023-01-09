#pragma once


namespace Orange
{
	struct Vertex
	{
		Float2 Position;
		FColor Color;

		Vertex(const Float2& position = Float2(), const FColor& color = FColor::White)
			:Position(position), Color(color)
		{
		}
	};
}
