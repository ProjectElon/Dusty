#pragma once

#include <cstring>

namespace math
{
	class Matrix4
	{
	public:
		float elements[4][4];

		Matrix4();
		Matrix4(float matrix[4][4]);
		Matrix4(const float& diagnal);
		Matrix4(const Matrix4& matrix);
		~Matrix4() = default;

		Matrix4& operator=(const Matrix4& matrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					elements[i][j] = matrix.elements[i][j];
				}
			}

			return *this;
		}

		Matrix4 operator+(const Matrix4& matrix) const
		{
			Matrix4 result;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					result.elements[i][j] = elements[i][j] + matrix.elements[i][j];
				}
			}

			return result;
		}

		Matrix4 operator-(const Matrix4& matrix) const
		{
			Matrix4 result;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					result.elements[i][j] = elements[i][j] - matrix.elements[i][j];
				}
			}

			return result;
		}

		Matrix4 operator*(const Matrix4& matrix) const
		{
			Matrix4 result;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					float sum = 0.0f;

					for (int k = 0; k < 4; ++k)
					{
						sum += elements[i][k] * matrix.elements[k][j];
					}

					result.elements[i][j] = sum;
				}
			}

			return result;
		}

		Matrix4 operator*(const float& scalar) const
		{
			Matrix4 result;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; ++j)
				{
					result.elements[i][j] *= scalar;
				}
			}

			return result;
		}

		Matrix4& operator*=(const Matrix4& matrix)
		{
			*this = *this * matrix;
			return *this;
		}

		Matrix4& operator*=(const float& scalar)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					elements[i][j] *= scalar;
				}
			}

			return *this;
		}

		Matrix4 operator/(const float& scalar) const
		{
			Matrix4 result;

			float inv = 1.0f / scalar;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; ++j)
				{
					result.elements[i][j] = elements[i][j] * inv;
				}
			}

			return result;
		}

		Matrix4& operator/=(const float& scalar)
		{
			float inv = 1.0f / scalar;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; ++j)
				{
					elements[i][j] *= inv;
				}
			}

			return *this;
		}

		static const Matrix4 Identity;
	};

}