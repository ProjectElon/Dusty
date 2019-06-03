#pragma once

#include "Functions.h"

#include <cassert>
#include <string>
#include <cstdio>

#define STR(x) std::to_string((x))

namespace math
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2();
		Vector2(const float& newX, const float& newY);
		Vector2(const Vector2& vector);
		~Vector2() = default;

		inline float LengthSq() const
		{
			return x * x + y * y;
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
		}

		inline Vector2 Normalized() const
		{
			Vector2 temp = *this;
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

		inline bool operator==(const Vector2& vector) const
		{
			return IsEqual(x, vector.x) && IsEqual(y, vector.y);
		}

		inline bool operator!=(const Vector2& vector) const
		{
			return !(*this == vector);
		}

		inline Vector2 operator+(const Vector2& vector) const
		{
			return Vector2(x + vector.x, y + vector.y);
		}

		inline Vector2 operator-(const Vector2& vector) const
		{
			return Vector2(x - vector.x, y - vector.y);
		}

		inline Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}

		inline Vector2& operator+=(const Vector2& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		inline Vector2& operator-=(const Vector2& vector)
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		inline Vector2 operator*(const float& scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		inline Vector2& operator*=(const float& scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		inline Vector2 operator/(const float& scalar) const
		{
			if (NearZero(scalar))
			{
				printf("division by zero\n");
				assert(false);
			}

			float inv = 1.0f / scalar;
			
			return Vector2(x * inv, y * inv);
		}

		inline Vector2& operator/=(const float& scalar)
		{
			if (NearZero(scalar))
			{
				printf("division by zero\n");
				assert(false);
			}

			float inv = 1.0f / scalar;
			
			x *= inv;
			y *= inv;

			return *this;
		}

		static inline float Dot(const Vector2& lhs, const Vector2& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		std::string ToString() const
		{
			return "(" + STR(x) + ", " + STR(y) + ")";
		}

		static const Vector2 Zero;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 NegUnitX;
		static const Vector2 NegUnitY;
	};

}