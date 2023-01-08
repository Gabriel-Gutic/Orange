#pragma once
#include "Vec2.h"


namespace Orange::Math
{
	const float pi = acosf(-1.0f);
	const float e = expf(1.0f);
	const float nan = std::nanf("");
	const float inf = std::numeric_limits<float>::infinity();

	unsigned int NumberOfDigits(int number);
	unsigned int NumberOfDigits(unsigned int number);
	unsigned int NumberOfDigits(long long number);
	unsigned int NumberOfDigits(unsigned long long number);
	std::string ToString(int number);
	std::string ToString(unsigned int number);
	std::string ToString(long long number);
	std::string ToString(unsigned long long number);
	std::string ToString(float number, unsigned int precision = 2);
	std::string ToString(double number, unsigned int precision = 2);
	std::string ToString(bool value);


	float Trunc(float number, unsigned int precision = 2);
	double Trunc(double number, unsigned int precision = 2);

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