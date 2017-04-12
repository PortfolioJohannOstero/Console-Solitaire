#pragma once

#include "Precision.h"

class Bounds;
class AsciiTexture
{
public:
	// @ Construction
	AsciiTexture();
	AsciiTexture(int width, int height, const rchar* texture);
	AsciiTexture(int width, int height, const rchar texture);
	AsciiTexture(const AsciiTexture& cpy);
	~AsciiTexture();

	// @ Operator
	AsciiTexture& operator = (const AsciiTexture& rhs);

	// @ Getters
	Bounds GetBoundary() const;
	rchar* GetTexture() const;

private:
	Bounds* mBoundary = nullptr;
	rchar* mTexture = nullptr;
};

