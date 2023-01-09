#pragma once


namespace Orange
{
	class FColor
	{
	public:
		union
		{
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				std::array<float, 4> rgba;
			};
			struct
			{
				std::array<float, 3> rgb;
			};
			struct
			{
				std::tuple<float, float, float, float> data;
			};
		};
	public:
		static FColor White;
		static FColor Black;
		static FColor Red;
		static FColor Green;
		static FColor Blue;
	public:
		FColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
		FColor(const FColor& other);
		~FColor() = default;
		FColor& operator=(const FColor& other);

		float* ToPtr();
		const float* ToPtr() const;

		float& operator[](uint32_t index);
		const float& operator[](uint32_t index) const;
	};
}
