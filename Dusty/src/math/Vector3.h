#pragma once

#include "Functions.h"

#include <cstdio>
#include <cassert>
#include <string>

#define STR(x) std::to_string((x))

namespace math
{
	class Vector2;

	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3();
		explicit Vector3(const float& newX, const float& newY, const float& newZ);
		Vector3(const Vector3& vector);

		~Vector3() = default;

		inline float LengthSq() const
		{
			return x * x + y * y + z * z;
		}

		inline float Length() const
		{
			return Sqrt(LengthSq());
		}

		inline void Normalize()
		{
			if (IsZero())
			{
				printf("division by zero\n");
				assert(false);
			}

			float inv = 1.0f / Length();

			x *= inv;
			y *= inv;
			z *= inv;
		}

		inline Vector3 Normalized() const
		{
			Vector3 temp = *this;
			temp.Normalize();
			return temp;
		}

		inline bool IsUnit() const
		{
			return IsEqual(LengthSq(), 1.0f);
		}

		inline bool IsZero() const
		{
			return NearZero(LengthSq());
		}

		inline bool operator==(const Vector3& vector) const
		{
			return IsEqual(x, vector.x) && IsEqual(y, vector.y) && IsEqual(z, vector.z);
		}

		inline bool operator!=(const Vector3& vector) const
		{
			return !(*this == vector);
		}

		inline Vector3 operator+(const Vector3& vector) const
		{
			return Vector3(x + vector.x, y + vector.y, z + vector.z);
		}

		inline Vector3 operator-(const Vector3& vector) const
		{
			return Vector3(x - vector.x, y - vector.y, z - vector.z);
		}

		inline Vector3 operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		inline Vector3& operator+=(const Vector3& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		inline Vector3& operator-=(const Vector3& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		inline Vector3 operator*(const float& scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		inline Vector3& operator*=(const float& scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		inline Vector3 operator/(const float& scalar) const
		{
			if (NearZero(scalar))
			{
				printf("division by zero\n");
				assert(false);
			}

			float inv = 1.0f / scalar;

			return Vector3(x * inv, y * inv, z * inv);
		}

		inline Vector3& operator/=(const float& scalar)
		{
			if (NearZero(scalar))
			{
				printf("division by zero\n");
				assert(false);
			}

			float inv = 1.0f / scalar;

			x *= inv;
			y *= inv;
			z *= inv;

			return *this;
		}

		static inline float Dot(const Vector3& lhs, const Vector3& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		static inline Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x
			);
		}

		Vector2 ToVector2() const;

		std::string ToString() const
		{
			return "(" + STR(x) + ", " + STR(y) + ", " + STR(z) + ")";
		}

		static const Vector3 Zero;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 NegUnitX;
		static const Vector3 NegUnitY;
		static const Vector3 NegUnitZ;
		static const Vector3 Infinity;
		static const Vector3 NegInfinity;
	};
}