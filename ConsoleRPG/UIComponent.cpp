#include "UIComponent.h"
#include "Vector2.h"

UIComponent::UIComponent(const Vector2& position, UIAlignment alignment, UIComponent* parent)
	: Object(position), mAlign(alignment)
{
	mParent = parent;

	if (mParent)
	{
		Vector2 parentPos = mParent->GetTransformedPosition();
		mTransformPos = new Vector2(parentPos + position);
		*mTransformPos += 1.0f;
		return;
	}
	mTransformPos = new Vector2(position);
}
UIComponent::UIComponent(const UIComponent& cpy) : Object(cpy)
{
	mAlign = cpy.mAlign;
	mParent = cpy.mParent;
	mTransformPos = new Vector2(*cpy.mTransformPos);
}

UIComponent::~UIComponent()
{
	delete mTransformPos;
	mTransformPos = nullptr;
}

// @ Getter
UIComponent* UIComponent::GetParent() const
{
	return mParent;
}

Vector2 UIComponent::GetTransformedPosition() const
{
	return *mTransformPos;
}