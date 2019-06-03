#pragma once

#include "Functions.h"

#include <cstdio>
#include <cassert>
#include <string>

#define STR(x) std::to_string((x))

namespace math
{
	class Vector3;

	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Vector4();
		Vector4(const float& newX, const float& newY, const float& newZ, const float& newW);
		Vector4(const math::Vector3& v, const float &newW);
		Vector4(const Vector4& vector);

		~Vector4() = default;

		inline float LengthSq() const
		{
			return x * x + y * y + z * z + w * w;
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
			w *= inv;
		}

		inline Vector4 Normalized() const
		{
			Vector4 temp = *this;
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

		inline bool operator==(const Vector4& vector) const
		{
			return IsEqual(x, vector.x) && IsEqual(y, vector.y) && IsEqual(z, vector.z);
		}

		inline bool operator!=(const Vector4& vector) const
		{
			return !(*this == vector);
		}

		inline Vector4 operator+(const Vector4& vector) const
		{
			return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
		}

		inline Vector4 operator-(const Vector4& vector) const
		{
			return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
		}

		inline Vector4 operator-() const
		{
			return Vector4(-x, -y, -z, -w);
		}

		inline Vector4& operator+=(const Vector4& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			w += vector.w;
			return *this;
		}

		inline Vector4& operator-=(const Vector4& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			w -= vector.w;
			return *this;
		}

		inline Vector4 operator*(const float& scalar) const
		{
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		inline Vector4& operator*=(const float& scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		inline Vector4 operator/(const float& scalar) const
		{
			if (NearZero(scalar))
			{
				printf("division by zero\n");
				assert(false);
			}

			float inv = 1.0f / scalar;

			return Vector4(x * inv, y * inv, z * inv, w * inv);
		}

		inline Vector4& operator/=(const float& scalar)
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
			w *= inv;

			return *this;
		}

		static inline Vector4 Hadamard(const Vector4& lhs, const Vector4& rhs)
		{
			return Vector4(
				lhs.x * rhs.x,
				lhs.y * rhs.y,
				lhs.z * rhs.z,
				lhs.w * rhs.w
			);
		}

		std::string ToString() const
		{
			return "(" + STR(x) + ", " + STR(y) + ", " + STR(z) + ", " + STR(w) + ")";
		}
	};
}