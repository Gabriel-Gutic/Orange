#include "pchOrange.h"
#include "Color.h"


namespace Orange
{
	FColor FColor::White = FColor(1.0f, 1.0f, 1.0f);
	FColor FColor::Black = FColor(0.0f, 0.0f, 0.0f);
	FColor FColor::Red   = FColor(1.0f, 0.0f, 0.0f);
	FColor FColor::Green = FColor(0.0f, 1.0f, 0.0f);
	FColor FColor::Blue  = FColor(0.0f, 0.0f, 1.0f);


	FColor::FColor(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a)
	{
	}

	FColor::FColor(const FColor& other)
	{
		if (this != &other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
		}
	}

	FColor& FColor::operator=(const FColor& other)
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

	float* FColor::ToPtr()
	{
		return rgba.data();
	}

	const float* FColor::ToPtr() const
	{
		return rgba.data();
	}

	float& FColor::operator[](uint32_t index)
	{
		return rgba[index];
	}

	const float& FColor::operator[](uint32_t index) const
	{
		return rgba[index];
	}
}