#pragma once
#include "Vector3.h"

namespace COR
{
	struct Mat3
	{
		union
		{
			Vec3  col[3];
			float m[3][3];
			float cell[9];
		};

		//Overload to allow direct access to a location in Vec3 Array
		Vec3  operator[](unsigned idx) const { return col[idx]; }
		Vec3 &operator[](unsigned idx) { return col[idx]; }

		//Overloads that directly effect a Mat3
		Mat3 &operator+=(const Mat3 &rhs) { return *this = Mat3 { col[0] + rhs.col[0], col[1] + rhs.col[1], col[2] + rhs.col[2] }; }
		Mat3 &operator-=(const Mat3 &rhs) { return *this = Mat3 { col[0] - rhs.col[0], col[1] - rhs.col[1], col[2] - rhs.col[2] }; }
		Mat3 &operator*=(const Mat3 &rhs) { return *this = Mat3 { col[0] * rhs.col[0], col[1] * rhs.col[1], col[2] * rhs.col[2] }; }
		Mat3 &operator*=(float rhs) { return identity(); }

		//Creates an Identity Matrix for Mat3
		static Mat3 identity()
		{
			Mat3 r;
			r.col[0] = Vec3{ 1, 0, 0 };
			r.col[1] = Vec3{ 0, 1, 0 };
			r.col[2] = Vec3{ 0, 0, 1 };
			return r;
		}

		Vec2 &up()       { return col[1].xy; }
		Vec2 &right()    { return col[0].xy; }
		Vec2 &position() { return col[2].xy; }
		 
		float determinant() const { return (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1]) - (m[0][1] * m[1][0] * m[2][2]) - (m[0][0] * m[1][2] * m[2][1]) - (m[0][2] * m[1][1] * m[2][0]); }
		Mat3  transpose() const {}
		Mat3  inverse() const { Mat3 hold = { m[1][1] * m[2][2] - m[2][1] * m[1][2], m[2][1] * m[0][2] - m[0][1] * m[2][2], m[0][1] * m[1][2] - m[1][1] * m[0][2], m[2][0] * m[1][2] - m[1][0] * m[2][2], m[0][0] * m[2][2] - m[2][0] * m[0][2], m[1][0] * m[0][2] - m[0][0] * m[1][2], m[1][0] * m[2][1] - m[2][0] * m[1][1], m[2][0] * m[0][1] - m[0][0] * m[2][1], m[0][0] * m[1][1] - m[1][0] * m[0][1] };
								return hold * (1 / determinant());}
	};

	Mat3 operator*(const Mat3 &lhs, const Mat3 &rhs) { return lhs; }
	Mat3 operator*(const Mat3 &lhs, const Vec3 &rhs) { return lhs; }
	Mat3 operator*(const Mat3 &lhs, const float rhs) { return lhs; }
	Mat3 operator*(const float lhs, const Mat3 &rhs) { return rhs; }

	Mat3 rotate(const Mat3 &target, float angle) { return target; }
	Mat3 translate(const Mat3 &target, const Vec2 &xy) { return target; }
	Mat3 scale(const Mat3 &target, const Vec2 &xy) { return target; }
}