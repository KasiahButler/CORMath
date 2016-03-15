#pragma once
#include <cmath>
#include <float.h>

namespace COR
{
	struct Vec2
	{
		//Vec2 Union of Data for Accessing in Different Ways
		union
		{
			float vec[2];
			struct { float x, y; };
		};

		//Direct Access Operator Overload for Vector
		float &operator[] (unsigned idx) { return vec[idx]; }
		float  operator[] (unsigned idx) const { return vec[idx]; }

		//Direct Vector Modification Operator Overloads
		Vec2 &operator+=(const Vec2 &rhs)  { return *this = Vec2{ x + rhs.x, y + rhs.y }; }
		Vec2 &operator-=(const Vec2 &rhs)  { return *this = Vec2{ x - rhs.x, y - rhs.y }; }
		Vec2 &operator*=(float rhs) { return *this = Vec2{ x * rhs, y * rhs }; }
		Vec2 &operator/=(float rhs) { return *this = Vec2{ x / rhs, y / rhs }; }

		//Unary Negation Operator Overload
		Vec2 &operator-() { return *this = Vec2{ -x, -y }; }

		//Functions that only effect or return data about *this
		float magnitude()	 const { return sqrtf(x*x + y*y); }
		float angle()		 const { return atan2f(y, x); }
		Vec2 normal()        const { return{ x / magnitude(), y / magnitude() }; }
		Vec2 perpendicular() const { return{ (y * -1), x }; }
	};

	//Operator Overloads for Add/Subtract/Multiply/Divide by Scalar and by Vector
	inline Vec2 operator+(const Vec2 &lhs, const Vec2 &rhs)
	{
		return{ lhs.x + rhs.x, lhs.y + rhs.y };
	}

	inline Vec2 operator+(const Vec2 &lhs, float rhs)
	{
		return{ lhs.x + rhs, lhs.y + rhs };
	}

	inline Vec2 operator-(const Vec2 &lhs, const Vec2 &rhs)
	{
		return{ lhs.x - rhs.x, lhs.x - rhs.x };
	}

	inline Vec2 operator*(const Vec2 &lhs, const Vec2 &rhs)
	{
		return{ lhs.x * rhs.x, lhs.y * rhs.y };
	}

	inline Vec2 operator*(const Vec2 &lhs, float rhs)
	{
		return{ lhs.x * rhs, lhs.y * rhs };
	}

	inline Vec2 operator*(float lhs, const Vec2 &rhs)
	{
		return rhs * lhs;
	}

	inline Vec2 operator/(const Vec2 &lhs, float rhs)
	{
		return{ lhs.x / rhs, lhs.y / rhs };
	}

	inline Vec2 operator/(float lhs, const Vec2 &rhs)
	{
		return rhs / lhs;
	}

	//Relation Operator Overloads

	inline bool operator==(const Vec2 &lhs, const Vec2 &rhs)
	{
		if (abs(lhs.x - rhs.x) <= FLT_EPSILON && abs(lhs.y == rhs.y) <= FLT_EPSILON) { return true; } return false;
	}

	inline bool operator!=(const Vec2 &lhs, const Vec2 &rhs)
	{
		if (lhs == rhs) { return false; } return true;
	}

	inline bool operator>(const Vec2 &lhs, const Vec2 &rhs)
	{
		if (lhs.x > rhs.x && lhs.y > rhs.y) { return true; } return false;
	}

	inline bool operator>=(const Vec2 &lhs, const Vec2 &rhs)
	{
		if (lhs > rhs || lhs == rhs) { return true; } return false;
	}

	inline bool operator<(const Vec2 &lhs, const Vec2 &rhs)
	{
		if (lhs.x < rhs.x && lhs.y < rhs.y) { return true; } return false;
	}

	inline bool operator<=(const Vec2 &lhs, const Vec2 &rhs)
	{
		if (lhs < rhs || lhs == rhs) { return true; } return false;
	}

	//Functions that need multiple Variables
	inline float dot(const Vec2 &lhs, const Vec2 &rhs)
	{
		return lhs.x *rhs.x + lhs.y * rhs.y;
	}

	inline float distance(const Vec2 &start, const Vec2 &end)
	{
		return end.magnitude() - start.magnitude();
	}

	inline float angleBetween(const Vec2 &start, const Vec2 &end)
	{
		return acosf(dot(start, end) / start.magnitude() * end.magnitude());
	}

	inline Vec2 fromAngle(float angle)
	{
		return{ cosf(angle), sinf(angle) };
	}

	inline Vec2 lerp(const Vec2 &start, const Vec2 &end, float percent)
	{
		return (end - start) * (start + percent);
	}

	inline Vec2 mix(const Vec2 &start, const Vec2 &end, float percent)
	{
		return start * (1 - percent) + end * percent;
	}

	inline Vec2 reflect(const Vec2 &incident, const Vec2 &normal)
	{
		return incident - (normal * 2 * (dot(incident, normal) * normal));
	}

	inline Vec2 project(const Vec2 &incident, const Vec2 &normal)
	{
		return (dot(incident, normal) * normal.normal());
	}

	inline Vec2 vmin(const Vec2 &lhs, const Vec2 &rhs)
	{
		return{ fminf(lhs.x, rhs.x), fminf(lhs.y, rhs.y) };
	}

	inline Vec2 vmax(const Vec2 &lhs, const Vec2 &rhs)
	{
		return{ fmaxf(lhs.x, rhs.x), fmaxf(lhs.y, rhs.y) };
	}

	inline Vec2 vclamp(const Vec2 &a, const Vec2 &max, const Vec2 &min)
	{
		return vmin(max, vmax(a, min));
	}
}