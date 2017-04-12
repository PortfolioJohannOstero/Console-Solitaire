#pragma once

#include "Precision.h"
#include "TextAlignment.h"
#include <string>

class Vector2;
class Bounds;
class AsciiTexture;
class View
{
public:
	// @ Construction
	View(int width, int height, rchar fillValue = L' ');
	~View();

	// @ Drawing
	/// Buffer filling
	void FillBuffer(float x, float y, rchar value);
	void FillBuffer(const Vector2& v, rchar value);

	void FillBuffer(float x, float y, const AsciiTexture& texture);
	void FillBuffer(const Vector2& v, const AsciiTexture& texture);

	void Clear();
	void SwapBuffers();

	// @ Getters
	Bounds GetBoundary() const;

private:

	// @ Helper Methods
	/// Windows Specific
	void SetConsolePosition(short x, short y);
	void ShowConsoleCursor(bool showFlag);
	void MaximizeWindow();

	int GetIndex(int x, int y);
	int GetIndex(const Vector2& v);
	void Swap();
	Bounds View::Clipping(const Bounds& textureBoundaries, float &x, float &y);

	rchar* mBuffer1 = nullptr;
	rchar* mBuffer2 = nullptr;

	rchar* mDrawBuffer = nullptr;
	rchar* mEditBuffer = nullptr;
	
	Bounds* mBoundary;
	rchar mClearSymbol;
};

