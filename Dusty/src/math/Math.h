#pragma once

#include "Functions.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Matrix4.h"

namespace math
{

	static Matrix3 Translation(const Vector2& T)
	{
		float translation[3][3] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			T.x,  T.y,  1.0f
		};

		return translation;
	}

	static Matrix3 Scale(const Vector2& S)
	{
		float scale[3][3] =
		{
			S.x,  0.0f, 0.0f,
			0.0f, S.y,  0.0f,
			0.0f, 0.0f, 1.0f
		};

		return scale;
	}

	static Matrix3 Rotation(const float& theta)
	{
		float sinTheta = Sin(theta);
		float cosTheta = Cos(theta);

		float rotation[3][3] = 
		{
			cosTheta, sinTheta, 0.0f,
		   -sinTheta, cosTheta, 0.0f,
			0.0f,     0.0f,     1.0f
		};

		return rotation;
	}

	static Matrix4 Translation(const Vector3& t)
	{
		float translation[4][4] =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			t.x,  t.y,  t.z,  1.0f
		};

		return translation;
	}

	static Matrix4 Translation(float x, float y, float z)
	{
		float translation[4][4] =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x,    y,    z,    1.0f
		};

		return translation;
	}

	static Matrix4 Scale(const Vector3& s)
	{
		float scale[4][4] =
		{
			s.x,  0.0f, 0.0f, 0.0f,
			0.0f, s.y,  0.0f, 0.0f,
			0.0f, 0.0f, s.z,  0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		return scale;
	}

	static Matrix4 Scale(float x, float y, float z)
	{
		float scale[4][4] =
		{
			x,    0.0f, 0.0f, 0.0f,
			0.0f, y,    0.0f, 0.0f,
			0.0f, 0.0f, z,    0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		return scale;
	}

	static Matrix4 RotationX(const float& pitch)
	{
		float sinPitch = Sin(pitch);
		float cosPitch = Cos(pitch);

		float rotationX[4][4] =
		{
			1.0f,  0.0f,     0.0f,     0.0f,
			0.0f,  cosPitch, sinPitch, 0.0f,
			0.0f, -sinPitch, cosPitch, 0.0f,
			0.0f,  0.0f,     0.0f,     1.0f
		};

		return rotationX;
	};

	static Matrix4 RotationY(const float& yaw)
	{
		float sinYaw = Sin(yaw);
		float cosYaw = Cos(yaw);

		float rotationY[4][4] =
		{
			cosYaw, 0.0f,  -sinYaw, 0.0f,
			0.0f,   1.0f,  0.0f,    0.0f,
			sinYaw, 0.0f,  cosYaw,  0.0f,
			0.0f,   0.0f,  0.0f,    1.0f
		};

		return rotationY;
	};

	static Matrix4 RotationZ(const float& roll)
	{
		float sinRoll = Sin(roll);
		float cosRoll = Cos(roll);

		float rotationZ[4][4] =
		{
			cosRoll,  sinRoll, 0.0f,  0.0f,
			-sinRoll, cosRoll, 0.0f,  0.0f,
			0.0f,     0.0f,    1.0f,  0.0f,
			0.0f,     0.0f,    0.0f,  1.0f
		};

		return rotationZ;
	}

	static Vector2 Transform(const Vector2& vec, const Matrix3& mat, float z = 1.0f)
	{
		Vector2 result;
		
		result.x = vec.x * mat.elements[0][0] + vec.y * mat.elements[1][0] + z * mat.elements[2][0];
		result.y = vec.x * mat.elements[0][1] + vec.y * mat.elements[1][1] + z * mat.elements[2][1];

		return result;
	}

	static Vector3 Transform(const Vector3& vec, const Matrix4& mat, float w = 1.0f)
	{
		Vector3 result;

		result.x = vec.x * mat.elements[0][0] + vec.y * mat.elements[1][0]
			     + vec.z * mat.elements[2][0] + w     * mat.elements[3][0];

		result.y = vec.x * mat.elements[0][1] + vec.y * mat.elements[1][1]
			     + vec.z * mat.elements[2][1] + w     * mat.elements[3][1];

		result.z = vec.x * mat.elements[0][2] + vec.y * mat.elements[1][2]
			     + vec.z * mat.elements[2][2] + w     * mat.elements[3][2];

		return result;
	}

	static inline Vector2 operator*(const Vector2& vec, const Matrix3& mat)
	{
		return Transform(vec, mat);
	}

	static inline Vector3 operator*(const Vector3& vec, const Matrix4& mat)
	{
		return Transform(vec, mat);
	}
}