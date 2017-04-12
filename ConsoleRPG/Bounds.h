#pragma once

class Vector2;
class Bounds
{
public:
	int left, right, top, bottom;

	// @ Construction
	Bounds(); /* <-- set eveyrhting to zero */
	Bounds(int l, int r, int t, int b);
	Bounds(int width, int height);
	Bounds(const Vector2& worldSpace, const Bounds& boundary);
	Bounds(const Bounds& cpy);

	// @ Set Dimensions
	void SetDimension(int l, int r, int t, int b);
	void SetDimension(int width, int height);
	void Translate(int x, int y);
	void Translate(const Vector2& pos);
	void Rotate(float angle, const Vector2& position);

	// @ Getters
	int GetWidth() const;
	int GetHeight() const;
	int GetArea() const;
	Vector2 GetCentre() const;

	// @ Collision Handling
	bool CompletelyOutside(const Bounds& rect, int x, int y);
	void ClipTo(const Bounds& rect);
	bool Contains(const Vector2& pos);

	// @ Operators
	#pragma region Operator Overloading
	Bounds& operator = (const Bounds& rhs);

	Bounds operator + (int rhs) const;
	Bounds operator - (int rhs) const;
	Bounds operator / (int rhs) const;
	Bounds operator * (int rhs) const;

	void operator += (int rhs);
	void operator -= (int rhs);
	void operator /= (int rhs);
	void operator *= (int rhs);

	Bounds operator + (const Bounds& rhs) const;
	Bounds operator - (const Bounds& rhs) const;
	Bounds operator / (const Bounds& rhs) const;
	Bounds operator * (const Bounds& rhs) const;

	void operator += (const Bounds& rhs);
	void operator -= (const Bounds& rhs);
	void operator /= (const Bounds& rhs);
	void operator *= (const Bounds& rhs);

	bool operator == (const Bounds& rhs) const;
	bool operator != (const Bounds& rhs) const;
	#pragma endregion
};

