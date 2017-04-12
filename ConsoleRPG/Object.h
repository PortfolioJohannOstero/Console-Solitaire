#pragma once

class View;
class Vector2;
class Object
{
public:
	// @ Construction
	Object();
	Object(const Vector2& position);
	Object(const Object& cpy);
	virtual ~Object();

	// @ Virtual methods
	virtual void Render(View& window) {}

	// @ Getters
	Vector2 GetPosition() const;
	bool GetIsActive() const;

	// @ Setters
	void SetPosition(const Vector2& position);
	void SetPosition(float x, float y);
	void SetActive(bool state);

	// @ Transformation
	void Translate(const Vector2& position);
	void Translate(float x, float y);

protected:
	Vector2* mPosition;
	bool mIsActive = true;
};

