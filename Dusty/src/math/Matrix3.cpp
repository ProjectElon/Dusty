#include "Matrix3.h"

namespace math
{
	const Matrix3 Matrix3::Identity(1.0f);

	Matrix3::Matrix3()
	{
		memset(elements, 0, sizeof(float) * 3 * 3);
	}

	Matrix3::Matrix3(float matrix[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				elements[i][j] = matrix[i][j];
			}
		}
	}

	Matrix3::Matrix3(const float& diagnal)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				elements[i][j] = (i == j) ? diagnal : 0.0f;
			}
		}
	}

	Matrix3::Matrix3(const Matrix3& matrix)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				elements[i][j] = matrix.elements[i][j];
			}
		}
	}
}