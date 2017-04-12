#include "UIText.h"
#include "AsciiTexture.h"
#include "View.h"
#include "Vector2.h"

// @ Construction
UIText::UIText(const Vector2& position, const std::wstring& text, UIAlignment alignment, UIComponent* parent)
	: UIComponent(position, alignment, parent), mText(text)
{
	mTexture = new AsciiTexture(text.size(), 1, text.c_str());
}
UIText::UIText(const UIText& cpy) : UIComponent(cpy)
{
	mText = cpy.mText;
	mTexture = new AsciiTexture(*cpy.mTexture);
}
UIText::~UIText()
{
	delete mTexture;
	mTexture = nullptr;
}

// @ Virtual
void UIText::Render(View& window)
{
	if(GetIsActive())
		window.FillBuffer(GetTransformedPosition(), *mTexture);
}

// @ Getters
std::wstring UIText::GetText()
{
	return mText;
}