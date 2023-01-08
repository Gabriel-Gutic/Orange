#pragma once


namespace Orange
{
	class Mat3
	{
	public:
		Mat3(float value = 0.0f);
		Mat3(const std::initializer_list<float>& data);
		Mat3(const Mat3& other);
		virtual ~Mat3() = default;

		Mat3& operator=(const Mat3& other);

		std::string ToString() const;

		float* ToPtr();
		const float* ToPtr() const;

		std::array<float, 3>& operator[](size_t index);
		const std::array<float, 3>& operator[](size_t index) const;

		friend Mat3 operator+(const Mat3& A, const Mat3& B);
		friend Mat3 operator-(const Mat3& A, const Mat3& B);
		friend Mat3 operator*(const Mat3& A, const Mat3& B);
		friend Mat3 operator*(const Mat3& A, float scalar);
		friend Mat3 operator/(const Mat3& A, float scalar);
		friend Mat3 operator*(float scalar, const Mat3& A);

		Mat3& operator+=(const Mat3& other);
		Mat3& operator-=(const Mat3& other);
		Mat3& operator*=(const Mat3& other);

		Mat3 Transpose() const;
		float Determinant() const;
		//Mat3 Inverse() const;
	private:
		std::array<std::array<float, 3>, 3> m_Buffer;
	};
}
