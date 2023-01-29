#pragma once
#include "Vec2.h"
#include "Mat3.h"


namespace Orange
{
	namespace Math
	{
		const float pi = acosf(-1.0f);
		const float e = expf(1.0f);
		const float nan = std::nanf("");
		const float inf = std::numeric_limits<float>::infinity();

		uint32_t NumberOfDigits(int number);
		uint32_t NumberOfDigits(uint32_t number);
		uint32_t NumberOfDigits(int64_t number);
		uint32_t NumberOfDigits(uint64_t number);
		std::string ToString(int number);
		std::string ToString(uint32_t number);
		std::string ToString(int64_t number);
		std::string ToString(uint64_t number);
		std::string ToString(float number, uint32_t precision = 2);
		std::string ToString(double number, uint32_t precision = 2);
		std::string ToString(bool value);


		//Generate random int64 value on the closed interval [a, b]
		int64_t RandomInt64(int64_t a = std::numeric_limits<int64_t>::min(), int64_t b = std::numeric_limits<int64_t>::max());

		//Generate random uint64 value on the closed interval [a, b]
		uint64_t RandomUInt64(uint64_t a = 0, uint64_t b = std::numeric_limits<uint64_t>::max());
		
		//Generate random int32 value on the closed interval [a, b]
		int RandomInt(int a = std::numeric_limits<int>::min(), int b = std::numeric_limits<int>::max());
		
		//Generate random uint32 value on the closed interval [a, b]
		uint32_t RandomUInt(uint32_t a = 0, uint32_t b = std::numeric_limits<uint32_t>::max());
		
		//Generate random floating-point value on the interval [a, b)
		float RandomFloat(float a = 0.0f, float b = 1.0f);


		float Trunc(float number, uint32_t precision = 2);
		double Trunc(double number, uint32_t precision = 2);

		bool IsNaN(float x);
		bool IsInf(float x);
		float Abs(float x);
		float Exp(float x);
		float Sqrt(float x);
		float Cbrt(float x);
		float RSqrt(float x);
		float Log(float x);
		float Log2(float x);
		float Log10(float x);
		float Log(float base, float x);
		float Pow(float a, float b);

		// Trigonometric Functions
		float Sin(float rad);
		float Cos(float rad);
		float Tan(float rad);

		float ASin(float rad);
		float ACos(float rad);
		float ATan(float rad);

		float Csc(float rad);
		float Sec(float rad);
		float Cot(float rad);

		float ACsc(float rad);
		float ASec(float rad);
		float ACot(float rad);

		float Sinh(float rad);
		float Cosh(float rad);
		float Tanh(float rad);

		float ASinh(float rad);
		float ACosh(float rad);
		float ATanh(float rad);

		float Csch(float rad);
		float Sech(float rad);
		float Coth(float rad);

		float ACsch(float rad);
		float ASech(float rad);
		float ACoth(float rad);

		// Angles
		float Radians(float degrees);
		float Degrees(float radians);


		template <typename T>
		T DotProduct(const Vec2<T>& v1, const Vec2<T>& v2);
		template <typename T>
		T Norm(const Vec2<T>& v);
		template <typename T>
		Vec2<T> Normalize(const Vec2<T>& v);


		Float2 Multiply(const Mat3& M, const Float2& V, float w = 1.0f);


		// Mat3 Functions:
		Mat3 Rotate(float degrees);
		Mat3 Scale(float xScale, float yScale);
		Mat3 Scale(const Float2& scale);
		Mat3 Translate(float x, float y);
		Mat3 Translate(const Float2& coords);


		template<typename T>
		T DotProduct(const Vec2<T>& v1, const Vec2<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		template<typename T>
		T Norm(const Vec2<T>& v)
		{
			return Sqrt(DotProduct(v, v));
		}

		template<typename T>
		Vec2<T> Normalize(const Vec2<T>& v)
		{
			return v * RSqrt(DotProduct(v, v));
		}
	}

	Float2 operator*(const Mat3& M, const Float2& V);
	Float2 operator*(const Float2& f2, float scalar);
	Float2 operator*(float scalar, const Float2& f2);
	Float2 operator/(const Float2& f2, float scalar);
}