#pragma once

#include <cstring>
#include <algorithm>

namespace math
{
	class Matrix3
	{
	public:
		float elements[3][3];

		Matrix3();
		Matrix3(float matrix[3][3]);
		Matrix3(const float& diagnal);
		Matrix3(const Matrix3& matrix);
		~Matrix3() = default;

		Matrix3& operator=(const Matrix3& matrix)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					elements[i][j] = matrix.elements[i][j];
				}
			}

			return *this;
		}

		Matrix3 operator+(const Matrix3& matrix) const
		{
			Matrix3 result;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					result.elements[i][j] = elements[i][j] + matrix.elements[i][j];
				}
			}

			return result;
		}

		Matrix3 operator-(const Matrix3& matrix) const
		{
			Matrix3 result;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					result.elements[i][j] = elements[i][j] - matrix.elements[i][j];
				}
			}

			return result;
		}

		Matrix3 operator*(const Matrix3& matrix) const
		{
			Matrix3 result;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					float sum = 0.0f;

					for (int k = 0; k < 3; ++k)
					{
						sum += elements[i][k] * matrix.elements[k][j];
					}

					result.elements[i][j] = sum;
				}
			}

			return result;
		}

		Matrix3 operator*(const float& scalar) const
		{
			Matrix3 result;
			
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; ++j)
				{
					result.elements[i][j] = elements[i][j] * scalar;
				}
			}

			return result;
		}

		Matrix3& operator*=(const Matrix3& matrix)
		{
			*this = *this * matrix;
			return *this;
		}

		Matrix3& operator*=(const float& scalar)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					elements[i][j] *= scalar;
				}
			}

			return *this;
		}

		Matrix3 operator/(const float& scalar) const
		{
			Matrix3 result;

			float inv = 1.0f / scalar;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; ++j)
				{
					result.elements[i][j] = elements[i][j] * inv;
				}
			}

			return result;
		}

		Matrix3& operator/=(const float& scalar)
		{
			float inv = 1.0f / scalar;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; ++j)
				{
					elements[i][j] *= inv;
				}
			}

			return *this;
		}

		static const Matrix3 Identity;
	};

}