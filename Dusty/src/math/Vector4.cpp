#include "Vector4.h"
#include "Vector3.h"

namespace math
{

	Vector4::Vector4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{}

	Vector4::Vector4(const float& newX, const float& newY, const float& newZ, const float& newW)
		: x(newX)
		, y(newY)
		, z(newZ)
		, w(newW)
	{}

	Vector4::Vector4(const math::Vector3& v, const float& newW)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(newW)
	{}

	Vector4::Vector4(const Vector4& vector)
		: x(vector.x)
		, y(vector.y)
		, z(vector.z)
		, w(vector.w)
	{}
}