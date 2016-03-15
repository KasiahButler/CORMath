#include "Collision.h"
#include "Defines.h"
#include "FMath.h"
#include <cmath>

namespace COR
{
	float rayPlaneDist(const Ray &ray, const Plane &plane)
	{
		return (dot(plane.normal, (ray.position - plane.position)) / -dot(plane.normal, ray.direction));
	}

	CollData CollTest(const Circle &lhs, const Circle &rhs)
	{
		CollData cd = { false };
		float depth = (lhs.radius + rhs.radius) - distance(lhs.position, rhs.position);

		if (depth > 0)
		{
			Vec2 norm = (lhs.position - rhs.position).normal();
			cd = { true, depth, norm };
		}
		else return cd = { false, depth, (lhs.position - rhs.position).normal() };
	}

	CollData CollTest(const Circle &lhs, const AABB &rhs)
	{
		CollData cd{ false };

		Vec2 cP = vclamp(lhs.position, rhs.min(), rhs.max());

		if (cP == lhs.position)
		{
			Vec2 d{ (cP.x - rhs.min().x < rhs.max().x - cP.x) ? rhs.min().x : rhs.max().x,
				(cP.y - rhs.min().y < rhs.max().y - cP.y) ? rhs.min().y : rhs.max().y };

			if (abs(d.x - cP.x) < abs(d.y - cP.y))
			{
				cP.x = d.x;
			}
			else cP.y = d.y;
		}

		float distSqr = distance(lhs.position, cP) * distance(lhs.position, cP);
		float radSqr = lhs.radius * lhs.radius;

		if (distSqr < radSqr)
		{
			cd.collision = true;
		}

		cd.depth = lhs.radius - distance(lhs.position, cP);

		cd.normal = (lhs.position - cP).normal();

		return cd;
	}

	CollData CollTest(const Circle &lhs, const Plane &rhs)
	{
		float cDot = dot(rhs.normal, (lhs.position - rhs.position));
		CollData cd{ false, (lhs.radius - cDot), rhs.normal };
		if (cDot <= lhs.radius)
		{
			cd.collision = true;
		}
		return cd;
	}

	CollData CollTest(const Circle &lhs, const Ray &rhs)
	{
		CollData cd = { false, 0, 0 };
		float cD = dot(lhs.position, rhs.position);
		float clPoint = fclamp(cD, 0, rhs.length);
		Vec2 closePoint = rhs.position + rhs.direction * clPoint;

		float cTest = dot((lhs.position - closePoint), (lhs.position - closePoint));

		if (cTest <= lhs.radius * lhs.radius)
		{
			//Need to determine Collision Normal and Penetration Depth.
			cd = { true, 0, 0 };
		}
		return cd;
	}

	CollData CollTest(const AABB &lhs, const AABB &rhs)
	{
		CollData cd{ false, 0, 0 };

		const float up = rhs.min().x - lhs.max().x;
		const float down = rhs.max().x - lhs.min().x;
		const float left = rhs.min().y - lhs.max().y;
		const float right = rhs.max().y - lhs.min().y;

		if (left < 0.0f || right > 0.0f || up < 0.0f || down > 0.0f) cd.collision = true;

		float collX = abs(left) < right ? left : right;
		float collY = abs(up) < down ? down : up;

		cd.depth = fminf(collX, collY);

		if (collX < collY) { cd.normal = (collX == right ? Vec2 RIGHT : Vec2 LEFT); }
		else cd.normal = (collY == up ? Vec2 UP : Vec2 DOWN);

		return cd;
	}

	CollData CollTest(const AABB &lhs, const Plane &rhs)
	{
		CollData cd{ false, 0, 0 };

		Vec2 localDis = lhs.position - rhs.position;

		float rectPlaneTest = lhs.halfextents.x * abs(dot(rhs.normal, RIGHT)) + lhs.halfextents.y * abs(dot(rhs.normal, UP));
		float penTest = rectPlaneTest - dot(rhs.normal, localDis);

		if (dot(rhs.normal, localDis) <= rectPlaneTest) cd = { true, penTest, rhs.normal };
		else cd = { false, penTest, rhs.normal };

		return cd;
	}

	CollData CollTest(const AABB &lhs, const Ray &rhs)
	{
		CollData cd = { false };

		// Min/Max along the X-Axis
		Plane s1p1 = Plane{ lhs.max(), RIGHT };
		Plane s1p2 = Plane{ lhs.min(), LEFT };
		float t11 = rayPlaneDist(rhs, s1p1); // Right
		float t12 = rayPlaneDist(rhs, s1p2); // Left
		float t1min = std::fminf(t11, t12);
		float t1max = std::fmaxf(t11, t12);
		Vec2  n1 = (t11 < t12) ? Vec2 RIGHT : Vec2 LEFT;

		// Min/Max along the Y-Axis
		Plane s2p1 = Plane{ lhs.max(), UP };
		Plane s2p2 = Plane{ lhs.min(), DOWN };
		float t21 = rayPlaneDist(rhs, s2p1);
		float t22 = rayPlaneDist(rhs, s2p2);
		float t2min = std::fminf(t21, t22);
		float t2max = std::fmaxf(t21, t22);
		Vec2  n2 = (t21 < t22) ? Vec2 UP : Vec2 DOWN;

		float tmin = std::fmaxf(t2min, t1min);
		float tmax = std::fminf(t2max, t1max);

		cd.depth = rhs.length - tmin;
		cd.collision = cd.depth >= 0 && tmin <= tmax && tmin > 0;
		cd.normal = (t1min > t2min) ? n1 : n2;

		return cd;
	}

	CollData CollTest(const Ray &lhs, const Plane &rhs)
	{
		CollData cd{ false, 0, 0 };
		Vec2 rLength = lhs.length * lhs.direction;
		Vec2 localDist = lhs.position - rhs.position;
		float rayPlaneTest = (dot(rhs.normal, localDist) / dot(rhs.normal, rLength) * -1);

		if (dot(rhs.normal, rLength) * -1 > 0) { return cd; }
		else if (rayPlaneTest >= 0 && rayPlaneTest <= lhs.length)
		{
			return cd = { true, lhs.length - rayPlaneTest, lhs.direction.normal() * -1 };
		}
	}
}