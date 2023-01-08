#pragma once


namespace Orange
{
	class Color
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
		static Color White;
		static Color Black;
		static Color Red;
		static Color Green;
		static Color Blue;
	public:
		Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
		Color(const Color& other);
		virtual ~Color() = default;
		Color& operator=(const Color& other);

		float* ToPtr();
		const float* ToPtr() const;

		float& operator[](uint32_t index);
		const float& operator[](uint32_t index) const;
	};
}
