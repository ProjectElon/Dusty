#pragma once

#include <cmath>
#include <limits>

namespace math
{
	const float Pi = 3.1315926535f;
	const float Epsilon = std::numeric_limits<float>::epsilon();
	const float Infinity = std::numeric_limits<float>::infinity();

	inline bool IsEqual(const float& a, const float& b)
	{
		return fabs(a - b) <= Epsilon;
	}

	inline bool NearZero(const float& scalar)
	{
		return fabs(scalar) <= Epsilon;
	}

	inline float ToRadians(const float& degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(const float& radians)
	{
		return radians * 180.0f / Pi;
	}

	template<typename T>
	inline T Max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}

	template<typename T>
	inline T Min(const T& a, const T& b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	inline T Clamp(const T& scalar, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, scalar));
	}

	inline float Abs(const float& scalar)
	{
		return fabs(scalar);
	}

	inline float Sqrt(const float& scalar)
	{
		return sqrtf(scalar);
	}

	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}

	inline float Sin(const float& angle)
	{
		return sinf(angle);
	}

	inline float Cos(const float& angle)
	{
		return cosf(angle);
	}

	inline float Tan(const float& angle)
	{
		return tanf(angle);
	}

	inline float Acos(const float& scalar)
	{
		return acosf(scalar);
	}

	inline float Atan2(const float& y, const float& x)
	{
		return atan2f(y, x);
	}

	template<typename T>
	inline T Lerp(const T& a, const T& b, const float& delta)
	{
		return a + (b - a) * delta;
	}
}