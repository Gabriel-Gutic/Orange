#include "pchOrange.h"
#include "Color.h"


namespace Orange
{
	Color Color::White = Color(1.0f, 1.0f, 1.0f);
	Color Color::Black = Color(0.0f, 0.0f, 0.0f);
	Color Color::Red   = Color(1.0f, 0.0f, 0.0f);
	Color Color::Green = Color(0.0f, 1.0f, 0.0f);
	Color Color::Blue  = Color(0.0f, 0.0f, 1.0f);


	Color::Color(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a)
	{
	}

	Color::Color(const Color& other)
	{
		if (this != &other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
		}
	}

	Color& Color::operator=(const Color& other)
	{
		if (this != &other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
		}
		return *this;
	}

	float* Color::ToPtr()
	{
		return rgba.data();
	}

	const float* Color::ToPtr() const
	{
		return rgba.data();
	}

	float& Color::operator[](uint32_t index)
	{
		return rgba[index];
	}

	const float& Color::operator[](uint32_t index) const
	{
		return rgba[index];
	}
}