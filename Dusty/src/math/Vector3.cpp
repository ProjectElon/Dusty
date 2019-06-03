#include "Vector3.h"
#include "Vector2.h"

namespace math
{
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.f);
	const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::NegUnitX(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::NegUnitY(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::NegUnitZ(0.0f, 0.0f, -1.0f);
	const Vector3 Vector3::Infinity(math::Infinity, math::Infinity, math::Infinity);
	const Vector3 Vector3::NegInfinity(-math::Infinity, -math::Infinity, -math::Infinity);

	Vector3::Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}
	
	Vector3::Vector3(const float& newX, const float& newY, const float &newZ)
		: x(newX)
		, y(newY)
		, z(newZ)
	{}

	Vector3::Vector3(const math::Vector2& v, const float& newZ)
		: x(v.x)
		, y(v.y)
		, z(newZ)
	{
	}
	
	Vector3::Vector3(const Vector3& vector)
		: x(vector.x)
		, y(vector.y)
		, z(vector.z)
	{}
}