#pragma once
#include <cmath>

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
	Vec2 &operator*=(const float &rhs) { return *this = Vec2{ x * rhs, y * rhs }; }
	Vec2 &operator/=(const float &rhs) { return *this = Vec2{ x / rhs, y / rhs }; }

	//Unary Negation Operator Overload
	Vec2 &operator-() { return{ -x, -y }; }

	//Functions that only effect or return data about the Vec2 itself
	float magnitude() const { return sqrtf(x*x + y*y); }
	float angle()     const { return atan2f(y, x); }

	Vec2 normal()        const { return{ x / magnitude(), y / magnitude() }; }
	Vec2 perpendicular() const { return{ (y * -1), x }; }
};

//Functions that need outside Variables
inline float dot(const Vec2 &lhs, const Vec2 &rhs)            
	{ return lhs.x *rhs.x + lhs.y * rhs.y; }

inline float distance(const Vec2 &start, const Vec2 &end)     
	{ return end.magnitude() - start.magnitude(); }

inline float angleBetween(const Vec2 &start, const Vec2 &end) 
	{ return acosf(dot(start, end) / start.magnitude() * end.magnitude()); }

inline Vec2 fromAngle(float angle)                           
	{ return{ cosf(angle), sinf(angle) }; }

inline Vec2 lerp(const Vec2 &start, const Vec2 &end, float percent) 
	{ return (end - start) * (start + percent); }

inline Vec2 mix(const Vec2 &start, const Vec2 &end, float percent) 
	{ return start * (1 - percent) + end * percent; }

inline Vec2 reflect(const Vec2 &incident, const Vec2 &normal)
	{ return incident - (normal * 2 * (dot(incident, normal) * normal)); }

inline Vec2 project(const Vec2 &incident, const Vec2 &normal)
	{ return (dot(incident, normal) * normal.normal()); }

//Operator Overloads for Add/Subtract/Multiply/Divide by Scalar and by Vector
inline Vec2 operator+(const Vec2 &lhs, const Vec2 &rhs)
	{ return{ lhs.x + rhs.x, lhs.y + rhs.y }; }

inline Vec2 operator+(const Vec2 &lhs, const float &rhs)
	{ return{ lhs.x + rhs, lhs.y + rhs }; }

inline Vec2 operator-(const Vec2 &lhs, const Vec2 &rhs)
	{ return{ lhs.x - rhs.x, lhs.x - rhs.x }; }

inline Vec2 operator*(const Vec2 &lhs, const Vec2 &rhs)
	{ return{ lhs.x * rhs.x, lhs.y * rhs.y }; }

inline Vec2 operator*(const Vec2 &lhs, const float &rhs)
	{ return{ lhs.x * rhs, lhs.y * rhs }; }

inline Vec2 operator*(const float &lhs, const Vec2 &rhs)
	{ return rhs * lhs; }

inline Vec2 operator/(const Vec2 &lhs, const float &rhs)
	{ return{ lhs.x / rhs, lhs.y / rhs }; }

inline Vec2 operator/(const float &lhs, const Vec2 &rhs)
	{ return rhs / lhs; }
