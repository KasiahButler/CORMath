#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include <vector>

namespace COR
{
	//ConvexHull needs work to ensure functionality
	struct ConvexHull
	{
		std::vector<Vec2> verts;
	};
	struct Ray
	{
		Vec2 position, direction;
		float length;
	};
	struct Plane
	{
		Vec2 position, normal;
	};
	struct Circle
	{
		Vec2 position;
		float radius;
	};
	struct AABB
	{
		Vec2 position, halfextents;
		Vec2 min() const, max() const;
	};

	inline Vec2 AABB::min() const { return position - halfextents; }
	inline Vec2 AABB::max() const { return position + halfextents; }


	//Useful for taking a gameobject's transform and applying it
	//to a shape for collision detection

	inline AABB operator*(const Mat3 &m, const AABB &a)
	{
		Vec2 omin = a.min();
		Vec2 omax = a.max();

		Vec2 rmin = m[2].xy;
		Vec2 rmax = m[2].xy;

		float p, q;

		for (unsigned j = 0; j < 2; ++j)
			for (unsigned i = 0; i < 2; ++i)
			{
				p = omin[i] * m[i][j];
				q = omax[i] * m[i][j];

				if (p < q) std::swap(p, q);
				rmin[j] += p;
				rmax[j] += q;
			}
		return{ (rmin + rmax) / 2, (rmin - rmax) / 2 };
	}

	inline Circle operator*(const Mat3 &mat, const Circle &circle)
	{
		Circle ret;
		ret.position = (mat * Vec3{ circle.position.x, circle.position.y, 1 }).xy;

		Vec3 xrad{ circle.radius, 0, 0 };
		Vec3 yrad{ 0, circle.radius, 0 };

		ret.radius = fmaxf((mat*xrad).magnitude(), (mat*yrad).magnitude());

		return ret;
	}

	inline Ray operator*(const Mat3 &m, const Ray &a)
	{
		Vec3 dir = Vec3{ a.direction.x, a.direction.y, 0 } *a.length;
		Vec3 pos{ a.position.x, a.position.y, 1 };

		return{ (m * pos).xy, (m * dir).xy.normal(), dir.magnitude() };
	}

	inline Plane operator*(const Mat3 &m, const Plane &a)
	{
		Vec3 nor{ a.normal.x, a.normal.y, 0 };
		Vec3 pos{ a.position.x, a.position.y, 1 };

		return{ (m*pos).xy, (m*nor).xy };
	}

	inline ConvexHull operator*(const Mat3 &m, const ConvexHull &a)
	{
		ConvexHull ret;
		for each(Vec2 p in ret.verts)
			ret.verts.push_back((m * Vec3{ p.x,p.y,1 }).xy);

		return ret;
	}
}