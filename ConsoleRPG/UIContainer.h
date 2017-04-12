#pragma once
#include "UIComponent.h"
#include "Precision.h"

class Bounds;
class AsciiTexture;
class UIContainer : public UIComponent
{
public:
	// @ Construction
	UIContainer(const Vector2& position, int width, int height, 
				UIAlignment alignment = UIAlignment::LEFT, 
				bool border = true, UIComponent* parent = nullptr);
	UIContainer(const UIContainer& cpy);
	~UIContainer();

	// @ Virtual
	void Render(View& window) override;

	// @ Getters
	Bounds GetBoundary() const;

private:
	AsciiTexture* mTexture = nullptr;

	// @ Helper method
	void ConstructBorder(int width, int height);

	const static rchar BORDER[];
	const static int TL_INDEX = 0;
	const static int TR_INDEX = 1;
	const static int BL_INDEX = 2;
	const static int BR_INDEX = 3;
	const static int H_INDEX = 4;
	const static int V_INDEX = 5;
	const static int FILL_INDEX = 6;
};

