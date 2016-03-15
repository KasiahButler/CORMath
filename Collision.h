#pragma once
#include "Shapes.h"

namespace COR
{
	struct CollData
	{
		bool collision;
		float depth;
		Vec2 normal;
	};

	//AABB Collision Tests
	CollData CollTest(const AABB &lhs, const AABB &rhs);

	//Circle Collision Tests
	CollData CollTest(const Circle &lhs, const Circle &rhs);
	CollData CollTest(const Circle &lhs, const AABB &rhs);
	CollData CollTest(const Circle &lhs, const Plane &rhs);
	CollData CollTest(const Circle &lhs, const Ray &rhs);

	//Ray Collision Tests
	CollData CollTest(const Ray &lhs, const Plane &rhs);
}