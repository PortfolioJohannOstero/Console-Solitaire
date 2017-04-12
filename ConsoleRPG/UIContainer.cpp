#include "UIContainer.h"
#include "Bounds.h"
#include "Vector2.h"
#include "View.h"
#include "AsciiTexture.h"

const rchar UIContainer::BORDER[]{ L"╔╗╚╝═║ " };

// @ Construction
UIContainer::UIContainer(const Vector2& position, int width, int height, UIAlignment alignment, bool border, UIComponent* parent)
	: UIComponent(position, alignment, parent)
{
	if (!border)
		mTexture = new AsciiTexture(width, height, BORDER[FILL_INDEX]);
	else
		ConstructBorder(width, height);

}
UIContainer::UIContainer(const UIContainer& cpy) : UIComponent(cpy)
{
	mTexture = new AsciiTexture(*cpy.mTexture);
}
UIContainer::~UIContainer()
{
	delete mTexture;
	mTexture = nullptr;
}

// @ Virtual
void UIContainer::Render(View& window)
{
	if(GetIsActive())
		window.FillBuffer(GetTransformedPosition(), *mTexture);
}

// @ Getters
Bounds UIContainer::GetBoundary() const
{
	return mTexture->GetBoundary();
}

// @ Helper method
void UIContainer::ConstructBorder(int width, int height)
{
	const int size = width * height;

	rchar* container = new rchar[size];
	wmemset(container, BORDER[FILL_INDEX], size);

	/// edges - horizontal
	int ht = 1;
	int hb = (height * width) - width;
	for (; ht < width; ht++, hb++)
	{
		container[ht] = BORDER[H_INDEX];
		container[hb] = BORDER[H_INDEX];
	}

	/// edges - vertical
	for (int y = 1; y < height-1; y++)
	{
		const int vl = width * y;
		const int vr = width * y + width-1;

		container[vl] = BORDER[V_INDEX];
		container[vr] = BORDER[V_INDEX];
	}

	/// corners
	container[0] = BORDER[TL_INDEX];
	container[width-1] = BORDER[TR_INDEX];
	container[height * width - width] = BORDER[BL_INDEX];
	container[size-1] = BORDER[BR_INDEX];

	mTexture = new AsciiTexture(width, height, container);

	delete[] container;
	container = nullptr;
}
