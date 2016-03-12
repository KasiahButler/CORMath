#pragma once
#include "Vector2.h"

struct Vec3
{
	//Vec3 Union for Accessing Data in different ways
	union
	{
		float vec[3];
		struct { float x, y, z; };
		Vec2 xy;
	};

	//Direct Access Operator Overload for Vector
	float &operator[] (unsigned idx) { return vec[idx]; }
	float  operator[] (unsigned idx) const { return vec[idx]; }
};