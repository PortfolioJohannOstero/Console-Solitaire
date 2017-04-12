#include "Vector2.h"

// @ Construction
#pragma region Construction
Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2::Vector2(const Vector2& v)
{
	x = v.x;
	y = v.y;
}
#pragma endregion

// @ Operations
Vector2& Vector2::operator = (const Vector2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector2& Vector2::operator + (const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}
void Vector2::operator += (const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}


/// Scalar
Vector2& Vector2::operator + (float scalar) const
{
	return Vector2(x + scalar, y + scalar);
}
void Vector2::operator += (float scalar)
{
	x += scalar;
	y += scalar;
}