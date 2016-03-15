#pragma once

namespace COR
{
	inline float fmin(float lhs, float rhs)
	{
		if (lhs < rhs) { return lhs; }
		return rhs;
	}

	inline float fmax(float lhs, float rhs)
	{
		if (lhs > rhs) { return lhs; }
		return lhs;
	}

	inline float fclamp(float a, float min, float max)
	{
		return fmin(max, fmax(a, min));
	}
}