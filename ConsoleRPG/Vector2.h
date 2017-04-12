#pragma once
class Vector2
{
public:
	// @ Construction
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& v);
	~Vector2() {}

	// @ Operations
	Vector2& operator = (const Vector2& rhs);

	Vector2& operator + (const Vector2& rhs) const;
	void operator += (const Vector2& rhs);
	
	/// Scalar
	Vector2& operator + (float scalar) const;
	void operator += (float scalar);

	float x, y;
};

