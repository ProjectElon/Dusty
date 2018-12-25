#include "Vector2.h"

namespace math
{
	const Vector2 Vector2::Zero(0.0f, 0.0f);
	const Vector2 Vector2::UnitX(1.0f, 0.0f);
	const Vector2 Vector2::UnitY(0.0f, 1.0f);
	const Vector2 Vector2::NegUnitX(-1.0f, 0.0f);
	const Vector2 Vector2::NegUnitY(0.0f, -1.0f);

	Vector2::Vector2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vector2::Vector2(const float& newX, const float& newY)
		: x(newX)
		, y(newY)
	{}
	
	Vector2::Vector2(const Vector2& vector)
		: x(vector.x)
		, y(vector.y)
	{}
}