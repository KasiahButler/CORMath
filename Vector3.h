#pragma once
#include "Vector2.h"

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
	Vec3 &operator*=(float &rhs)      { return *this = Vec3{ x * rhs, y * rhs, z * rhs }; }
	Vec3 &operator/=(float &rhs)      { return *this = Vec3{ x / rhs, y / rhs, z / rhs }; }

	//Unary Negation Overload
	Vec3 &operator-() { return{ -x, -y, -z }; }

	//Functions that only use Data from *this
	float magnitude() const { return sqrtf(x * x + y * y + z * z); }
	Vec3 normal()     const { return { x / magnitude(), y / magnitude(), z / magnitude() }; }
};

inline float dot(const Vec3 &lhs, const Vec3 &rhs)			   { return 0; }
inline float distance(const Vec3 &start, const Vec3 &end)	   { return 0; }
inline float angleBetween(const Vec3 &start, const Vec3 &end) { return 0; }

inline Vec3 cross(const Vec3 &lhs, const Vec3 &rhs) { return{ 0, 0, 0 }; }

inline Vec3 mix(const Vec3 &start, const Vec3 &end, float percent)  { return{ 0, 0, 0 }; }
inline Vec3 lerp(const Vec3 &start, const Vec3 &end, float percent) { return{ 0, 0, 0 }; }

inline Vec3 reflect(const Vec3 &incident, const Vec3 &normal) { return{ 0, 0, 0 }; }
inline Vec3 project(const Vec3 &incident, const Vec3 &normal) { return{ 0, 0, 0 }; }

inline Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs) { return{ 0, 0, 0 }; }
inline Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs) { return{ 0, 0, 0 }; }

inline Vec3 operator*(const Vec3 &lhs, float &rhs) { return{ 0, 0, 0 }; }
inline Vec3 operator*(float &lhs, const Vec3 &rhs) { return{ 0, 0, 0 }; }

inline Vec3 operator/(const Vec3 &lhs, float &rhs) { return{ 0, 0, 0 }; }
inline Vec3 operator/(float &lhs, const Vec3 &rhs) { return{ 0, 0, 0 }; }