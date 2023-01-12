#pragma once


namespace Orange
{
	struct Vertex
	{
		Float2 Position;
		FColor Color;
		Float2 TexCoords;
		float TexIndex;

		Vertex(const Float2& position = Float2(), const FColor& color = FColor::White, const Float2& texCoords = Float2(), float texIndex = -1.0f)
			:Position(position), Color(color), TexCoords(texCoords), TexIndex(texIndex)
		{
		}
	};
}
