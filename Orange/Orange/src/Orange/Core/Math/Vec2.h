#pragma once


namespace Orange
{
	template <typename T>
	class Vec2
	{
	public:
		union
		{
			struct
			{
				std::array<T, 2> data;
			};
			struct
			{
				std::pair<T, T> pair;
			};
			struct
			{
				T x, y;
			};
		};
	public:
		Vec2(const T& x = T(), const T& y = T());
		Vec2(const Vec2& other);
		~Vec2() = default;

		Vec2& operator=(const Vec2& other);

		template <typename T>
		friend Vec2 operator+(const Vec2& v1, const Vec2& v2);
		template <typename T>
		friend Vec2 operator-(const Vec2& v1, const Vec2& v2);
		template <typename T>
		friend Vec2 operator*(const Vec2& v1, const Vec2& v2);
		template <typename T>
		friend Vec2 operator/(const Vec2& v1, const Vec2& v2);
		
		T& operator[](uint32_t index);
		const T& operator[](uint32_t index) const;

		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator/=(const Vec2& other);
	};

	using Int2 = Vec2<int>;
	using UInt2 = Vec2<unsigned int>;
	using Float2 = Vec2<float>;
	using Double2 = Vec2<double>;

	template<typename T>
	inline Vec2<T>::Vec2(const T& x, const T& y)
		:x(x), y(y)
	{
	}

	template<typename T>
	inline Vec2<T>::Vec2(const Vec2& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
	}

	template<typename T>
	inline Vec2<T>& Vec2<T>::operator=(const Vec2<T>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	template<typename T>
	inline T& Vec2<T>::operator[](uint32_t index)
	{
		return data[index];
	}

	template<typename T>
	inline const T& Vec2<T>::operator[](uint32_t index) const
	{
		return data[index];
	}

	template<typename T>
	inline Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& other)
	{
		x = x + other.x;
		y = y + other.y;
		return *this;
	}

	template<typename T>
	inline Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& other)
	{
		x = x - other.x;
		y = y - other.y;
		return *this;
	}

	template<typename T>
	inline Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& other)
	{
		x = x * other.x;
		y = y * other.y;
		return *this;
	}

	template<typename T>
	inline Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& other)
	{
		x = x / other.x;
		y = y / other.y;
		return *this;
	}

	template<typename T>
	Vec2<T> operator+(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return Vec2<T>(v1.x + v2.x, v1.y + v2.y);
	}

	template<typename T>
	Vec2<T> operator-(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return Vec2<T>(v1.x - v2.x, v1.y - v2.y);
	}

	template<typename T>
	Vec2<T> operator*(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return Vec2<T>(v1.x * v2.x, v1.y * v2.y);
	}

	template<typename T>
	Vec2<T> operator/(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return Vec2<T>(v1.x / v2.x, v1.y / v2.y);
	}
}
