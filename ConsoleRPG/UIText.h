#pragma once
#include "UIComponent.h"
#include "TextAlignment.h"
#include <string>

class AsciiTexture;
class UIText : public UIComponent
{
public:
	// @ Construction
	UIText(const Vector2& position, const std::wstring& text, 
		   UIAlignment alignment = UIAlignment::LEFT, UIComponent* parent = nullptr);
	UIText(const UIText& cpy);
	virtual ~UIText();

	// @ Virtual
	void Render(View& window) override;

	// @ Getters
	std::wstring GetText();

private:
	AsciiTexture* mTexture = nullptr;
	std::wstring mText;
};

