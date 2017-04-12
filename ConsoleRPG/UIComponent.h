#pragma once

#include "Object.h"
#include "UIAlignment.h"

class AsciiTexture;
class UIComponent : public Object
{
public:
	// @ Construction
	UIComponent(const Vector2& position, UIAlignment alignment = UIAlignment::LEFT, UIComponent* parent = nullptr);
	UIComponent(const UIComponent& cpy);
	virtual ~UIComponent();

	virtual void Render(View& window) override = 0;

	// @ Getter
	UIComponent* GetParent() const;
	Vector2 GetTransformedPosition() const;

private:
	UIAlignment mAlign;
	UIComponent* mParent = nullptr;
	Vector2* mTransformPos = nullptr;
};

