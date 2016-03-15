#pragma once
#include "Vector2.h"
#include <cmath>
#include <float.h>

namespace COR
{
	struct Vec3
	{
		//Vec3 Union for Accessing Data in different ways
		union
		{
			float vec[3];
			struct { float x, y, z; };
			struct { float r, g, b; };
			Vec2 xy;
		};

		//Direct Access Operator Overload for Vector
		float &operator[] (unsigned idx) { return vec[idx]; }
		float  operator[] (unsigned idx) const { return vec[idx]; }

		//Operator Overloads that Modify this Vector
		Vec3 &operator+=(const Vec3 &rhs) { return *this = Vec3{ x + rhs.x, y + rhs.y, z + rhs.z }; }
		Vec3 &operator-=(const Vec3 &rhs) { return *this = Vec3{ x - rhs.x, y - rhs.y, z - rhs.z }; }
		Vec3 &operator*=(float rhs) { return *this = Vec3{ x * rhs, y * rhs, z * rhs }; }
		Vec3 &operator/=(float rhs) { return *this = Vec3{ x / rhs, y / rhs, z / rhs }; }

		//Unary Negation Overload
		Vec3 &operator-() { return *this = Vec3{ -x, -y, -z }; }

		//Functions that only use Data from *this
		float magnitude() const { return sqrtf(x * x + y * y + z * z); }
		Vec3 normal()     const { return{ x / magnitude(), y / magnitude(), z / magnitude() }; }
	};
	//Operator Overloads for Vector3 Math
	inline Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs)
	{
		return{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}

	inline Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs)
	{
		return{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	inline Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs)
	{
		return{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
	}

	inline Vec3 operator*(const Vec3 &lhs, float rhs)
	{
		return{ lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
	}

	inline Vec3 operator*(float lhs, const Vec3 &rhs)
	{
		return rhs * lhs;
	}

	inline Vec3 operator/(const Vec3 &lhs, float rhs)
	{
		return{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
	}

	inline Vec3 operator/(float lhs, const Vec3 &rhs)
	{
		return rhs / lhs;
	}

	//Relational Operator Overloads for Vector3
	inline bool operator==(const Vec3 &lhs, const Vec3 &rhs)
	{
		if (abs(lhs.x - rhs.x) <= FLT_EPSILON && abs(lhs.y - rhs.y) <= FLT_EPSILON && abs(lhs.z - rhs.z) <= FLT_EPSILON) { return true; } return false;
	}

	inline bool operator!=(const Vec3 &lhs, const Vec3 &rhs)
	{
		if (lhs == rhs) { return false; } return true;
	}

	inline bool operator>(const Vec3 &lhs, const Vec3 &rhs)
	{
		if (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z) { return true; } return false;
	}

	inline bool operator>=(const Vec3 &lhs, const Vec3 &rhs) 
	{
		if (lhs > rhs || lhs == rhs) { return true; } return false;
	}

	inline bool operator<(const Vec3 &lhs, const Vec3 &rhs)
	{
		if (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z) { return true; } return false;
	}

	inline bool operator<=(const Vec3 &lhs, const Vec3 &rhs) 
	{ 
		if (lhs < rhs || lhs == rhs) { return true; } return false; 
	}

	//Functions that require multiple variables to be passed in
	inline float dot(const Vec3 &lhs, const Vec3 &rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	inline float distance(const Vec3 &start, const Vec3 &end)
	{
		return end.magnitude() - start.magnitude();
	}

	inline Vec3 cross(const Vec3 &lhs, const Vec3 &rhs)
	{
		return{ lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
	}

	inline Vec3 mix(const Vec3 &start, const Vec3 &end, float percent)
	{
		return (start * (1 - percent)) + (end * percent);
	}

	inline Vec3 lerp(const Vec3 &start, const Vec3 &end, float percent)
	{
		return (end - start * percent + start);
	}

	inline Vec3 reflect(const Vec3 &incident, const Vec3 &normal)
	{
		return incident - (2 * dot(incident, normal) * normal);
	}

	inline Vec3 project(const Vec3 &incident, const Vec3 &normal)
	{
		return dot(incident, normal) * normal.normal();
	}

	inline Vec3 vmin(const Vec3 &lhs, const Vec3 &rhs)
	{
		return{ fminf(lhs.x, rhs.x), fminf(lhs.y, rhs.y), fminf(lhs.z, rhs.z) };
	}

	inline Vec3 vmax(const Vec3 &lhs, const Vec3 &rhs)
	{
		return{ fmaxf(lhs.x, rhs.x), fmaxf(lhs.y, rhs.y), fmaxf(lhs.z, rhs.z) };
	}

	inline Vec3 vclamp(const Vec3 &a, const Vec3 &min, const Vec3 &max)
	{
		return vmin(max, vmax(a, min));
	}
}