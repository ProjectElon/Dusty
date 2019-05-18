#include "Matrix4.h"

namespace math
{
	const Matrix4 Matrix4::Identity;

	Matrix4::Matrix4()
	{
		memset(elements, 0, sizeof(float) * 4 * 4);
	}

	Matrix4::Matrix4(float matrix[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				elements[i][j] = matrix[i][j];
			}
		}
	}

	Matrix4::Matrix4(const float& diagnal)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				elements[i][j] = (i == j) ? diagnal : 0.0f;
			}
		}
	}

	Matrix4::Matrix4(const Matrix4& matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				elements[i][j] = matrix.elements[i][j];
			}
		}
	}
}