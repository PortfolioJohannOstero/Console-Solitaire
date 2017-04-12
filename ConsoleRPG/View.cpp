#include "View.h"
#include <iostream>
#include <assert.h>

#include "Vector2.h"
#include "AsciiTexture.h"
#include "Bounds.h"

#include <Windows.h>
#include <vector>

// @ Construction
View::View(int width, int height, rchar clearSymbol)
	: mClearSymbol(clearSymbol)
{
	mBoundary = new Bounds(width, height);
	const int size = mBoundary->GetArea();

	mBuffer1 = new rchar[size+1];
	mBuffer2 = new rchar[size+1];

	memset(mBuffer1, clearSymbol, size-1);
	memset(mBuffer2, clearSymbol, size-1);

	mBuffer1[size] = '\0';
	mBuffer2[size] = '\0';

	mEditBuffer = mBuffer1;
	mDrawBuffer = mBuffer2;	

	ShowConsoleCursor(false);
	MaximizeWindow();
}
View::~View()
{
	delete[] mBuffer1;
	mBuffer1 = nullptr;

	delete[] mBuffer2;
	mBuffer2 = nullptr;

	delete mBoundary;
	mBoundary = nullptr;
}

// @ Drawing
void View::FillBuffer(float x, float y, rchar value)
{
	if (x < 0 || x > mBoundary->GetWidth())
		return;

	if (y < 0 || y > mBoundary->GetHeight())
		return;

	mEditBuffer[GetIndex((int)x, (int)y)] = value;
}
void View::FillBuffer(const Vector2& v, rchar value)
{
	FillBuffer(v.x, v.y, value);
}

void View::FillBuffer(float x, float y, const AsciiTexture& texture)
{
	Bounds tBounds = texture.GetBoundary();
	rchar* tRef = texture.GetTexture();

	if (tBounds.CompletelyOutside(*mBoundary, (int)x, (int)y))
		return;

	const Bounds Clipped = Clipping(tBounds, x, y);
	const size_t charSize = sizeof(rchar);

	rchar* destination = mEditBuffer + ((int)x + (int)y * mBoundary->GetWidth()) * charSize;
	rchar* source = tRef + (Clipped.left + Clipped.top * tBounds.GetWidth()) * charSize;

	for (int y = 0; y < Clipped.GetHeight(); y++)
	{
		memcpy(destination, source, Clipped.GetWidth() * charSize);

		source += tBounds.GetWidth();
		destination += mBoundary->GetWidth();
	}
}
void View::FillBuffer(const Vector2& v, const AsciiTexture& texture)
{
	FillBuffer(v.x, v.y, texture);
}

void View::Clear()
{
	wmemset(mEditBuffer, mClearSymbol, mBoundary->GetArea());
	SetConsolePosition(0,0);
}
void View::SwapBuffers()
{
	Swap();
	const int height = mBoundary->GetHeight();
	const int width = mBoundary->GetWidth();

	std::wstring derp;
	derp.reserve(height * width + height);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			derp.push_back(mDrawBuffer[GetIndex(j, i)]);
		derp.push_back('\n');
	}

	wprintf(L"%s", derp);
}

// @ Getters
Bounds View::GetBoundary() const
{
	return *mBoundary;
}


// @ Helper Methods

/// Windows Specific Methods
void View::SetConsolePosition(short x, short y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x,y });
}
void View::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void View::MaximizeWindow()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SMALL_RECT rc;
	rc.Left = rc.Top = 0;
	rc.Right = (short)(min(info.dwMaximumWindowSize.X, info.dwSize.X) - 1);
	rc.Bottom = (short)(min(info.dwMaximumWindowSize.Y, info.dwSize.Y) - 1);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);
}

int View::GetIndex(int x, int y)
{
	return x + y * mBoundary->GetWidth();
}
int View::GetIndex(const Vector2& v)
{
	return GetIndex((int)v.x, (int)v.y);
}

void View::Swap()
{
	rchar* temp = mEditBuffer;
	mEditBuffer = mDrawBuffer;
	mDrawBuffer = temp;
}

Bounds View::Clipping(const Bounds& textureBoundaries, float &x, float &y)
{
	const int xi = (int)x;
	const int yi = (int)y;

	Bounds Clipped(0, textureBoundaries.GetWidth(), 0, textureBoundaries.GetHeight()); /* 1. source space */
	Clipped.Translate(xi, yi); /* 2. Convert to screen space */
	Clipped.ClipTo(*mBoundary); /* 3. Clip to window */
	Clipped.Translate(-xi, -yi); /* 4. Convert back to source space */

	/* 5. clamp x and y values if they go below 0 */
	if (xi < 0) x = 0;
	if (yi < 0) y = 0;

	return Clipped;
}