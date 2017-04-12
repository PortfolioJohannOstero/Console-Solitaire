#include "Object.h"
#include "Vector2.h"

// @ Construction
Object::Object()
{
	mPosition = new Vector2(0.0f, 0.0f);
}
Object::Object(const Vector2& position)
{
	mPosition = new Vector2(position.x, position.y);
}
Object::Object(const Object& cpy)
{
	Vector2 otherPos = cpy.GetPosition();

	if (!mPosition)
		mPosition = new Vector2(otherPos.x, otherPos.y);
	else
	{
		mPosition->x = otherPos.x;
		mPosition->y = otherPos.y;
	}
}
Object::~Object()
{
	delete mPosition;
	mPosition = nullptr;
}

// @ Getters
Vector2 Object::GetPosition() const
{
	return *mPosition;
}
bool Object::GetIsActive() const
{
	return mIsActive;
}

// @ Setters
void Object::SetPosition(const Vector2& position)
{
	*mPosition = position;
}
void Object::SetPosition(float x, float y)
{
	SetPosition(Vector2(x, y));
}
void Object::SetActive(bool state)
{
	mIsActive = state;
}

// @ Transformation
void Object::Translate(const Vector2& position)
{
	*mPosition += position;
}
void Object::Translate(float x, float y)
{
	Translate(Vector2(x, y));
}