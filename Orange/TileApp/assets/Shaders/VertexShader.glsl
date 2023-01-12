#version 330 core
layout (location = 0) in vec2 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 TexCoords;
layout (location = 3) in float TexIndex;

out vec4 o_Color;
out vec2 o_TexCoords;
out float o_TexIndex;


void main()
{
	o_Color = Color;
	o_TexCoords = TexCoords;
	o_TexIndex = TexIndex;
	gl_Position = vec4(Position, 0.0f, 1.0f);
}