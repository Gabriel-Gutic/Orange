#version 330 core
layout (location = 0) in vec2 Position;
layout (location = 1) in vec4 Color;

out vec4 o_Color;

void main()
{
	o_Color = Color;
	gl_Position = vec4(Position, 0.0f, 1.0f);
}