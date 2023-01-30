#version 330 core

in vec4 o_Color;
in vec2 o_TexCoords;
in float o_TexIndex;

out vec4 FragColor;

uniform sampler2D u_Textures[32];


void main()
{
	if (o_Color.a == 0.0f)
		discard;

	if (o_TexIndex < 0.0f)
	{
		FragColor = o_Color;
	}
	else
	{
		int index = int(o_TexIndex + 0.1);
		FragColor = o_Color * texture(u_Textures[index], o_TexCoords);
		if (FragColor.a < 0.5f)
			discard;
	}
}