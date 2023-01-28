#include "pchOrange.h"
#include "MathFunctions.h"


namespace Orange
{
	uint32_t Math::NumberOfDigits(int number)
	{
		return (uint32_t)log10(number) + 1;
	}

	uint32_t Math::NumberOfDigits(uint32_t number)
	{
		return (uint32_t)log10(number) + 1;
	}

	uint32_t Math::NumberOfDigits(int64_t number)
	{
		return (uint32_t)log10(number) + 1;
	}

	uint32_t Math::NumberOfDigits(uint64_t number)
	{
		return (uint32_t)log10(number) + 1;
	}

	std::string Math::ToString(int number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(uint32_t number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(int64_t number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(uint64_t number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(float number, uint32_t precision)
	{
		long long a = (long long)number;
		float b = Abs(number - a);

		for (uint32_t i = 0; i < precision; i++)
			b *= 10;

		long long c = (long long)b;
		while (c % 10 == 0 && c != 0)
			c /= 10;

		if (c == 0)
			return std::to_string(a);
		return std::to_string(a) + "." + std::to_string(c);
	}

	std::string Math::ToString(double number, uint32_t precision)
	{
		long long a = (long long)number;
		double b = Abs(number - a);

		for (uint32_t i = 0; i < precision; i++)
			b *= 10;

		long long c = (long long)b;
		while (c % 10 == 0 && c != 0)
			c /= 10;

		if (c == 0)
			return std::to_string(a);
		return std::to_string(a) + "." + std::to_string(c);
	}

	std::string Math::ToString(bool value)
	{
		return value ? "True" : "False";
	}

	float Math::Trunc(float number, uint32_t precision)
	{
		uint32_t power = 1;
		for (uint32_t i = 0; i < precision; i++)
			power *= 10;
		return floorf(number * power) / static_cast<float>(power);
	}

	double Math::Trunc(double number, uint32_t precision)
	{
		uint32_t power = 1;
		for (uint32_t i = 0; i < precision; i++)
			power *= 10;
		return floor(number * power) / static_cast<double>(power);
	}

	bool Math::IsNaN(float x)
	{
		return std::isnan(x);
	}

	bool Math::IsInf(float x)
	{
		return std::isinf(x);
	}

	float Math::Sqrt(float x)
	{
		if (x < 0)
			return nan;
		return sqrtf(x);
	}

	float Math::Cbrt(float x)
	{
		return cbrtf(x);
	}

	// 1 / sqrt(x)
	float Math::RSqrt(float x)
	{
		if (x == 0)
			return inf;
		if (x < 0)
			return nan;

		int i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = x * 0.5F;
		y = x;
		i = *(int*)&y;							// evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);				// what the fuck? 
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));	// 1st iteration
		y = y * (threehalfs - (x2 * y * y));	// 2nd iteration, this can be removed

		return y;
	}

	float Math::Abs(float x)
	{
		if (x < 0.0f)
			return -x;
		return x;
	}

	float Math::Exp(float x)
	{
		return expf(x);
	}

	float Math::Log(float x)
	{
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return logf(x);
	}

	float Math::Log2(float x)
	{
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return log2f(x);
	}

	float Math::Log10(float x)
	{
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return log10f(x);
	}

	float Math::Log(float base, float x)
	{
		if (base == 1 || base <= 0)
			return nan;
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return Log(x) / Log(base);
	}

	float Math::Pow(float a, float b)
	{
		return powf(a, b);
	}

	float Math::Sin(float rad)
	{
		return sinf(rad);
	}

	float Math::Cos(float rad)
	{
		return cosf(rad);
	}

	float Math::Tan(float rad)
	{
		return tanf(rad);
	}

	float Math::ASin(float rad)
	{
		if (-1.0f > rad || rad > 1.0f)
		{
			ORANGE_ERROR("ASin invalid parameter: {0}", rad);
			return nan;
		}
		return asinf(rad);
	}

	float Math::ACos(float rad)
	{
		if (rad < -1.0f || rad > 1.0f)
		{
			ORANGE_ERROR("ACos invalid parameter: {0}", rad);
			return nan;
		}
		return acosf(rad);
	}

	float Math::ATan(float rad)
	{
		return atanf(rad);
	}

	float Math::Csc(float rad)
	{
		float _sin = Sin(rad);
		if (_sin == 0.0f)
		{
			ORANGE_ERROR("Csc invalid parameter: {0}", rad);
			return nan;
		}
		return 1.0f / _sin;
	}

	float Math::Sec(float rad)
	{
		float _cos = Cos(rad);
		if (_cos == 0.0f)
		{
			ORANGE_ERROR("Sec invalid parameter: {0}", rad);
			return nan;
		}
		return 1.0f / _cos;
	}

	float Math::Cot(float rad)
	{
		float _tan = Tan(rad);
		if (_tan == 0.0f)
		{
			ORANGE_ERROR("Cot invalid parameter: {0}", rad);
			return nan;
		}
		return 1.0f / _tan;
	}

	float Math::ACsc(float rad)
	{
		if (rad == 0.0f)
		{
			ORANGE_ERROR("ACsc invalid argument: {0}", rad);
			return nan;
		}
		return ASin(1.0f / rad);
	}

	float Math::ASec(float rad)
	{
		if (rad == 0.0f)
		{
			ORANGE_ERROR("ACsc invalid argument: {0}", rad);
			return nan;
		}
		return ACos(1.0f / rad);
	}

	float Math::ACot(float rad)
	{
		if (rad == 0.0f)
		{
			ORANGE_ERROR("ACsc invalid argument: {0}", rad);
			return nan;
		}
		return ATan(1.0f / rad);
	}

	float Math::Sinh(float rad)
	{
		return sinhf(rad);
	}

	float Math::Cosh(float rad)
	{
		return coshf(rad);
	}

	float Math::Tanh(float rad)
	{
		return tanhf(rad);
	}

	float Math::ASinh(float rad)
	{
		return asinh(rad);
	}

	float Math::ACosh(float rad)
	{
		return acosh(rad);
	}

	float Math::ATanh(float rad)
	{
		return atanh(rad);
	}

	float Math::Csch(float rad)
	{
		float _sinh = Sinh(rad);
		if (_sinh == 0.0f)
		{
			ORANGE_ERROR("Csch invalid argument: {0}", rad);
			return nan;
		}
		return 1.0f / _sinh;
	}

	float Math::Sech(float rad)
	{
		float _sech = Sech(rad);
		if (_sech == 0.0f)
		{
			ORANGE_ERROR("Sech invalid argument: {0}", rad);
			return nan;
		}
		return 1.0f / _sech;
	}

	float Math::Coth(float rad)
	{
		float _tanh = Tanh(rad);
		if (_tanh == 0.0f)
		{
			ORANGE_ERROR("Coth invalid argument: {0}", rad);
			return nan;
		}
		return 1.0f / _tanh;
	}

	float Math::ACsch(float rad)
	{
		if (rad == 0.0f)
		{
			ORANGE_ERROR("ACsch invalid argument: {0}", rad);
			return nan;
		}
		return ASinh(1.0f / rad);
	}

	float Math::ASech(float rad)
	{
		if (rad == 0.0f)
		{
			ORANGE_ERROR("ASech invalid argument: {0}", rad);
			return nan;
		}
		return ACosh(1.0f / rad);
	}

	float Math::ACoth(float rad)
	{
		if (rad == 0.0f)
		{
			ORANGE_ERROR("ACoth invalid argument: {0}", rad);
			return nan;
		}
		return ATanh(1.0f / rad);
	}

	float Math::Radians(float degrees)
	{
		return degrees * (pi / 180);
	}

	float Math::Degrees(float radians)
	{
		return radians * (180 / pi);
	}

	Float2 Math::Multiply(const Mat3& M, const Float2& V, float w)
	{
		return Float2(
			M[0][0] * V[0] + M[0][1] * V[1] + M[0][2] * w,
			M[1][0] * V[0] + M[1][1] * V[1] + M[1][2] * w
			);
	}

	Float2 operator*(const Mat3& M, const Float2& V)
	{
		return Math::Multiply(M, V);
	}

	Float2 operator*(const Float2& f2, float scalar)
	{
		return Float2(f2.x * scalar, f2.y * scalar);
	}

	Float2 operator*(float scalar, const Float2& f2)
	{
		return f2 * scalar;
	}

	Float2 operator/(const Float2& f2, float scalar)
	{
		return Float2(f2.x / scalar, f2.y / scalar);
	}

	Mat3 Math::Rotate(float degrees)
	{
		Mat3 M(1.0f);

		float radians = Math::Radians(degrees);

		M[0][0] =  Math::Cos(radians);
		M[0][1] = -Math::Sin(radians);
		M[1][0] =  Math::Sin(radians);
		M[1][1] =  Math::Cos(radians);

		return M;
	}

	Mat3 Math::Scale(float xScale, float yScale)
	{
		Mat3 M(1.0f);
		M[0][0] = xScale;
		M[1][1] = yScale;
		return M;
	}

	Mat3 Math::Scale(const Float2& scale)
	{
		return Scale(scale.x, scale.y);
	}

	Mat3 Math::Translate(float x, float y)
	{
		Mat3 M(1.0f);
		M[0][2] = x;
		M[1][2] = y;
		return M;
	}

	Mat3 Math::Translate(const Float2& coords)
	{
		return Translate(coords.x, coords.y);
	}
}