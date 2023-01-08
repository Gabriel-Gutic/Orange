#version 330 core

in vec2 o_Position;

out vec4 FragColor;

void main()
{
	FragColor = vec4(o_Position, 0.0f, 1.0f);
}