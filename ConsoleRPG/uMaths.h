#pragma once

#include <algorithm>

namespace util
{
	void Clamp(int& value, int max, int min = 0)
	{
		value = std::min(value, max);
		value = std::max(value, min);
	}
}