#pragma once
#include "Object.h"
#include <string>
#include <vector>

class UIContainer;
class UIText;
class ObjectPopup : public Object
{
public:
	// @ Construction
	ObjectPopup(const Vector2& position, int width, int height, const std::wstring& header);
	virtual ~ObjectPopup();
	
	// @ Virtual
	void Render(View& window) override;

	// @ Action
	void AddText(const Vector2& relativePosition, const std::wstring& text);
	void AddLine(const std::wstring& text);
private:
	UIContainer* mContainer = nullptr;
	UIText* mHeader = nullptr;
	std::vector<UIText*> mText;

};

