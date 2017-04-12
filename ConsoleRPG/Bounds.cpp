#include "Bounds.h"
#include "Vector2.h"

/* +==== Constructors ====+ */
Bounds::Bounds() :left(0), right(0), top(0), bottom(0) {}
Bounds::Bounds(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
Bounds::Bounds(int width, int height) : left(0), right(width), top(0), bottom(height) {}

Bounds::Bounds(const Vector2& worldSpace, const Bounds& boundary)
{
	left = (int)worldSpace.x;
	right = (int)worldSpace.x + boundary.GetWidth();

	top = (int)worldSpace.y;
	bottom = (int)worldSpace.y + boundary.GetHeight();
}

/* +=== Copy ===+ */
Bounds::Bounds(const Bounds& cpy)
{
	left   = cpy.left;
	right  = cpy.right;
	top	   = cpy.top;
	bottom = cpy.bottom;
}

/* +==== Get Dimension ====+ */
#pragma region Get Dimension
int Bounds::GetWidth() const
{
	return right - left;
}

int Bounds::GetHeight() const
{
	return bottom - top;
}

int Bounds::GetArea() const
{
	return GetWidth() * GetHeight();
}

Vector2 Bounds::GetCentre() const
{
	return Vector2(GetWidth() / 2.f, GetHeight() / 2.f);
}
#pragma endregion

/* +==== Set dimension ====+ */
#pragma region Set Dimension
void Bounds::SetDimension(int l, int r, int t, int b)
{
	left = l;
	right = r;
	top = t;
	bottom = b;
}

void Bounds::SetDimension(int width, int height)
{
	SetDimension(0, width, 0, height);
}

void Bounds::Translate(int x, int y)
{
	left += x;
	right += x;

	top += y;
	bottom += y;
}

void Bounds::Translate(const Vector2& pos)
{
	Translate((int)pos.x, (int)pos.y);
}

// TODO: Rotate corners
void Bounds::Rotate(float angle, const Vector2& position)
{
	Vector2& center = GetCentre();
}
#pragma endregion

/* +==== Collider Handling ====+ */
#pragma region Collider Handling
bool Bounds::CompletelyOutside(const Bounds& rect, int x, int y)
{
	return x >	rect.right ||
		y >	rect.bottom ||
		x <	rect.left - GetWidth() ||
		y <	rect.top - GetHeight();
}

void Bounds::ClipTo(const Bounds& rect)
{
	if (left < rect.left)
		left = rect.left;
	if (right > rect.right)
		right = rect.right;

	if (top < rect.top)
		top = rect.top;
	if (bottom > rect.bottom)
		bottom = rect.bottom;
}

bool Bounds::Contains(const Vector2& pos)
{
	return pos.x > left && pos.x < right &&
		pos.y > top && pos.y < bottom;
}
#pragma endregion

/* +==== Operator Overloading ====+ */
#pragma region Operator Overloading
Bounds& Bounds::operator = (const Bounds& rhs)
{
	left = rhs.left;
	right = rhs.right;
	top = rhs.top;
	bottom = rhs.bottom;
	return *this;
}

Bounds Bounds::operator + (int rhs) const
{
	Bounds rect = *this;
	rect.left += rhs;
	rect.right += rhs;
	rect.top += rhs;
	rect.bottom += rhs;
	return rect;
}

Bounds Bounds::operator - (int rhs) const
{
	Bounds rect = *this;
	rect.left -= rhs;
	rect.right -= rhs;
	rect.top -= rhs;
	rect.bottom -= rhs;
	return rect;
}

Bounds Bounds::operator / (int rhs) const
{
	Bounds rect = *this;
	rect.left /= rhs;
	rect.right /= rhs;
	rect.top /= rhs;
	rect.bottom /= rhs;
	return rect;
}

Bounds Bounds::operator * (int rhs) const
{
	Bounds rect = *this;
	rect.left *= rhs;
	rect.right *= rhs;
	rect.top *= rhs;
	rect.bottom *= rhs;
	return rect;
}

void Bounds::operator += (int rhs)
{
	left += rhs;
	right += rhs;
	top += rhs;
	bottom += rhs;
}

void Bounds::operator -= (int rhs)
{
	left -= rhs;
	right -= rhs;
	top -= rhs;
	bottom -= rhs;
}

void Bounds::operator /= (int rhs)
{
	left /= rhs;
	right /= rhs;
	top /= rhs;
	bottom /= rhs;
}

void Bounds::operator *= (int rhs)
{
	left *= rhs;
	right *= rhs;
	top *= rhs;
	bottom *= rhs;
}

Bounds Bounds::operator + (const Bounds& rhs) const
{
	Bounds rect = *this;
	rect.left += rhs.left;
	rect.right += rhs.right;
	rect.top += rhs.top;
	rect.bottom += rhs.bottom;
	return rect;
}

Bounds Bounds::operator - (const Bounds& rhs) const
{
	Bounds rect = *this;
	rect.left -= rhs.left;
	rect.right -= rhs.right;
	rect.top -= rhs.top;
	rect.bottom -= rhs.bottom;
	return rect;
}
Bounds Bounds::operator / (const Bounds& rhs) const
{
	Bounds rect = *this;
	rect.left /= rhs.left;
	rect.right /= rhs.right;
	rect.top /= rhs.top;
	rect.bottom /= rhs.bottom;
	return rect;
}

Bounds Bounds::operator * (const Bounds& rhs) const
{
	Bounds rect = *this;
	rect.left *= rhs.left;
	rect.right *= rhs.right;
	rect.top *= rhs.top;
	rect.bottom *= rhs.bottom;
	return rect;
}


void Bounds::operator += (const Bounds& rhs)
{
	left += rhs.left;
	right += rhs.right;
	top += rhs.top;
	bottom += rhs.bottom;
}

void Bounds::operator -= (const Bounds& rhs)
{
	left -= rhs.left;
	right -= rhs.right;
	top -= rhs.top;
	bottom -= rhs.bottom;
}

void Bounds::operator /= (const Bounds& rhs)
{
	left /= rhs.left;
	right /= rhs.right;
	top /= rhs.top;
	bottom /= rhs.bottom;
}

void Bounds::operator *= (const Bounds& rhs)
{
	left *= rhs.left;
	right *= rhs.right;
	top *= rhs.top;
	bottom *= rhs.bottom;
}

bool Bounds::operator == (const Bounds& rhs) const
{
	return left == rhs.left  &&
		right == rhs.right &&
		top == rhs.top   &&
		bottom == rhs.bottom;
}
bool Bounds::operator != (const Bounds& rhs) const
{
	return left != rhs.left  &&
		right != rhs.right &&
		top != rhs.top   &&
		bottom != rhs.bottom;
}

#pragma endregion