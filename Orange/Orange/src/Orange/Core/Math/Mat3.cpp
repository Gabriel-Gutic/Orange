#include "pchOrange.h"
#include "Mat3.h"


namespace Orange
{
	Mat3::Mat3(float value)
		:m_Buffer({})
	{
		if (value != 0.0f)
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					m_Buffer[i][j] = (i == j) ? value : 0.0f;
		}
	}

	Mat3::Mat3(const std::initializer_list<float>& data)
		:m_Buffer({})
	{
		for (int i = 0; i < 9 && i < data.size(); i++)
		{
			m_Buffer[i / 3][i % 3] = *(data.begin() + i);
		}
	}

	Mat3::Mat3(const Mat3& other)
	{
		if (this != &other)
		{
			m_Buffer = other.m_Buffer;
		}
	}

	Mat3& Mat3::operator=(const Mat3& other)
	{
		if (this != &other)
		{
			m_Buffer = other.m_Buffer;
		}
		return *this;
	}

	std::string Mat3::ToString() const
	{
		std::stringstream ss;
		ss << "[[" << m_Buffer[0][0] << ", " << m_Buffer[0][1] << ", " << m_Buffer[0][2] << "], "
			<< "[" << m_Buffer[1][0] << ", " << m_Buffer[1][1] << ", " << m_Buffer[1][2] << "], "
			<< "[" << m_Buffer[2][0] << ", " << m_Buffer[2][1] << ", " << m_Buffer[2][2] << "]]";

		return ss.str();
	}

	float* Mat3::ToPtr()
	{
		return m_Buffer.data()->data();
	}

	const float* Mat3::ToPtr() const
	{
		return m_Buffer.data()->data();
	}

	std::array<float, 3>& Mat3::operator[](size_t index)
	{
		return m_Buffer[index];
	}

	const std::array<float, 3>& Mat3::operator[](size_t index) const
	{
		return m_Buffer[index];
	}

	Mat3& Mat3::operator+=(const Mat3& other)
	{
		*this = *this + other;
		return *this;
	}

	Mat3& Mat3::operator-=(const Mat3& other)
	{
		*this = *this - other;
		return *this;
	}

	Mat3& Mat3::operator*=(const Mat3& other)
	{
		*this = *this * other;
		return *this;
	}

	Mat3 Mat3::Transpose() const
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result[i][j] = m_Buffer[j][i];
		return result;
	}

	float Mat3::Determinant() const
	{
		return 
			m_Buffer[0][0] * m_Buffer[1][1] * m_Buffer[2][2] 
			+ m_Buffer[0][2] * m_Buffer[1][0] * m_Buffer[2][1]
			+ m_Buffer[0][1] * m_Buffer[1][2] * m_Buffer[2][0]
			- m_Buffer[0][2] * m_Buffer[1][1] * m_Buffer[2][0]
			- m_Buffer[0][0] * m_Buffer[1][2] * m_Buffer[2][1]
			- m_Buffer[0][1] * m_Buffer[1][0] * m_Buffer[2][2];
	}

	/*Mat3 Mat3::Inverse() const
	{
		return Mat3();
	}*/

	Mat3 operator+(const Mat3& A, const Mat3& B)
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result[i][j] = A[i][j] + B[i][j];
		return result;
	}

	Mat3 operator-(const Mat3& A, const Mat3& B)
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result[i][j] = A[i][j] - B[i][j];
		return result;
	}

	Mat3 operator*(const Mat3& A, const Mat3& B)
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
			for (int k = 0; k < 3; k++)
				for (int j = 0; j < 3; j++)
					result[i][j] += result[i][k] + result[k][j];
		return result;
	}

	Mat3 operator*(const Mat3& A, float scalar)
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result[i][j] = scalar * A[i][j];
		return result;
	}

	Mat3 operator/(const Mat3& A, float scalar)
	{
		return A * (1.0f / scalar);
	}

	Mat3 operator*(float scalar, const Mat3& A)
	{
		return A * scalar;
	}
}