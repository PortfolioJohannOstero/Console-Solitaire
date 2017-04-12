#include "AsciiTexture.h"
#include "Bounds.h"

#include <iostream>

// @ Construction
#pragma region Construction
AsciiTexture::AsciiTexture()
{
	mBoundary = new Bounds(1, 1);
	mTexture = new rchar[2];
	mTexture[0] = '?';
	mTexture[1] = '\0';

}
AsciiTexture::AsciiTexture(int width, int height, const rchar* texture)
{
	mBoundary = new Bounds(width, height);
	const int size = mBoundary->GetArea();

	mTexture = new rchar[size+1];
	memcpy(mTexture, texture, size * sizeof(rchar));
	mTexture[size] = '\0';
}
AsciiTexture::AsciiTexture(int width, int height, const rchar texture)
{
	mBoundary = new Bounds(width, height);
	int size = mBoundary->GetArea();

	mTexture = new rchar[size+1];
	memset(mTexture, texture, size * sizeof(rchar));
	mTexture[size] = '\0';
}

AsciiTexture::AsciiTexture(const AsciiTexture& cpy)
{
	const rchar* cpyTexture = cpy.GetTexture();
	mBoundary = new Bounds(cpy.GetBoundary());
	
	const int size = mBoundary->GetArea();

	mTexture = new rchar[size+1];
	memcpy(mTexture, cpyTexture, size * sizeof(rchar));
	mTexture[size] = '\0';
}
AsciiTexture::~AsciiTexture()
{
 	/*delete[] mTexture;
	mTexture = nullptr;
	
	delete mBoundary;
	mBoundary = nullptr;*/
}
#pragma endregion

// @ Operators
AsciiTexture& AsciiTexture::operator = (const AsciiTexture& rhs)
{
	if (this == &rhs)
		return *this;

	if (mBoundary)
	{
		delete mBoundary;
		mBoundary = nullptr;
	}
	mBoundary = new Bounds(rhs.GetBoundary());
	if (mTexture)
	{
		delete[] mTexture;
		mTexture = nullptr;
	}
	mTexture = new rchar[mBoundary->GetArea()];
	
	// Fill up Texture
	rchar* otherTexture = rhs.GetTexture();
	wmemcpy(mTexture, otherTexture, mBoundary->GetArea());
	return *this;
}

// @ Getters
Bounds AsciiTexture::GetBoundary() const
{
	return *mBoundary;
}
rchar* AsciiTexture::GetTexture() const
{ 
	return mTexture; 
}
