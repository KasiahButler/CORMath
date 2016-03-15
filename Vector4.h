#pragma once
#include "Vector3.h"
#include <cmath>
#include <float.h>

namespace COR
{
	struct Vec4
	{
		//Vec3 Union for Accessing Data in different ways
		union
		{
			float vec[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, y; };
			Vec3 xyz;
			Vec2 xy;
		};

		//Direct Access Operator Overload for Vector
		float &operator[] (unsigned idx) { return vec[idx]; }
		float  operator[] (unsigned idx) const { return vec[idx]; }

		//Operator Overloads that Modify this Vector
		Vec4 &operator+=(const Vec4 &rhs) { return *this = Vec4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }
		Vec4 &operator-=(const Vec4 &rhs) { return *this = Vec4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }
		Vec4 &operator*=(float rhs) { return *this = Vec4{ x * rhs, y * rhs, z * rhs, w * rhs }; }
		Vec4 &operator/=(float rhs) { return *this = Vec4{ x / rhs, y / rhs, z / rhs, w * rhs }; }

		//Unary Negation Overload
		Vec4 &operator-() { return *this = Vec4{ -x, -y, -z, -w }; }

		//Functions that only use Data from *this
		float magnitude() const { return sqrtf(x * x + y * y + z * z + w * w); }
		Vec4 normal()     const { return{ x / magnitude(), y / magnitude(), z / magnitude(), w / magnitude() }; }
	};

	//Math Operator Overloads for Vector4
	inline Vec4 operator+(const Vec4 &lhs, const Vec4 &rhs)
	{
		return{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
	}

	inline Vec4 operator-(const Vec4 &lhs, const Vec4 &rhs)
	{
		return{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
	}

	inline Vec4 operator*(const Vec4 &lhs, const Vec4 rhs)
	{
		return{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w };
	}

	inline Vec4 operator*(const Vec4 &lhs, float rhs)
	{
		return{ lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs };
	}

	inline Vec4 operator*(float lhs, const Vec4 &rhs)
	{
		return rhs * lhs;
	}

	inline Vec4 operator/(const Vec4 &lhs, float rhs)
	{
		return{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs };
	}

	inline Vec4 operator/(float lhs, const Vec4 &rhs)
	{
		return rhs / lhs;
	}

	//Relational Operator Overloads for Vector4
	inline bool operator>(const Vec4 &lhs, const Vec4 &rhs)
	{
		if (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w) { return true; } return false;
	}

	inline bool operator>=(const Vec4 &lhs, const Vec4 &rhs)
	{
		return false;
	}

	inline bool operator<(const Vec4 &lhs, const Vec4 &rhs)
	{
		if (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w) { return true; } return false;
	}

	inline bool operator<=(const Vec4 &lhs, const Vec4 &rhs)
	{
		return false;
	}

	inline bool operator==(const Vec4 &lhs, const Vec4 &rhs)
	{
		if (abs(lhs.x - rhs.x) <= FLT_EPSILON && abs(lhs.y - rhs.y) <= FLT_EPSILON && abs(lhs.z - rhs.z) <= FLT_EPSILON && abs(lhs.w - rhs.w) <= FLT_EPSILON) { return true; } return false;
	}

	inline bool operator!=(const Vec4 &lhs, const Vec4 &rhs)
	{
		if (lhs == rhs) { return false; } return true;
	}

	//Functions that require multiple variables for Vector4
	inline float dot(const Vec4 &lhs, const Vec4 &rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}

	inline float distance(const Vec4 &start, const Vec4 &end)
	{
		return end.magnitude() - start.magnitude();
	}

	inline Vec4 mix(const Vec4 &start, const Vec4 &end, float percent)
	{
		return start * (1 - percent) + end * percent;
	}

	inline Vec4 lerp(const Vec4 &start, const Vec4 &end, float percent)
	{
		return end - start * percent + start;
	}

	inline Vec4 reflect(const Vec4 &incident, const Vec4 &normal)
	{
		return incident - 2 * dot(incident, normal) * normal;
	}

	inline Vec4 project(const Vec4 &incident, const Vec4 &normal)
	{
		return dot(incident, normal) * normal.normal();
	}

	inline Vec4 vmin(const Vec4 &lhs, const Vec4 &rhs)
	{
		return{ fminf(lhs.x, rhs.x), fminf(lhs.y, rhs.y), fminf(lhs.z, rhs.z), fminf(lhs.w, rhs.w) };
	}

	inline Vec4 vmax(const Vec4 &lhs, const Vec4 &rhs)
	{
		return{ fmaxf(lhs.x, rhs.x), fmaxf(lhs.y, rhs.y), fmaxf(lhs.z, rhs.z), fmaxf(lhs.w, rhs.w) };
	}

	inline Vec4 vclamp(const Vec4 &a, const Vec4 &min, const Vec4 &max)
	{
		return vmin(max, vmax(a, min));
	}
}