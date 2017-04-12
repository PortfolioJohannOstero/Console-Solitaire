#include "ObjectPopup.h"
#include "UIContainer.h"
#include "UIText.h"
#include "Vector2.h"

ObjectPopup::ObjectPopup(const Vector2& position, int width, int height, const std::wstring& header)
{
	mContainer = new UIContainer(position, width, height);

	mHeader = new UIText({ 0.0f, 0.0f }, header, UIAlignment::LEFT, mContainer);
}
ObjectPopup::~ObjectPopup()
{
	delete mContainer;
	mContainer = nullptr;

	delete mHeader;
	mHeader = nullptr;

	for (UIText* t : mText)
	{
		delete t;
		t = nullptr;
	}
	mText.clear();
}

void ObjectPopup::Render(View& window)
{
	if (!GetIsActive())
		return;

	mContainer->Render(window);
	mHeader->Render(window);

	for (UIText* text : mText)
		text->Render(window);
}

void ObjectPopup::AddText(const Vector2& relativePosition, const std::wstring& text)
{
	UIText* newText = new UIText(relativePosition, text, UIAlignment::LEFT, mContainer);
	mText.push_back(newText);
}
void ObjectPopup::AddLine(const std::wstring& text)
{
	Vector2 relPos;
	if (!mText.empty())
		relPos = mText[mText.size() - 1]->GetPosition();
	relPos.y += 1.0f;

	AddText(relPos, text);
}