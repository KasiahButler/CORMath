#pragma once
#include <iostream>
#include "Vector4.h"

namespace COR
{
	struct Mat4
	{
		union
		{
			Vec4  col[4];
			float m[4][4];
			float cell[16];
		};

		//Overload to allow direct access to a location in Vec3 Array
		Vec4  operator[](unsigned idx) const { return col[idx]; }
		Vec4 &operator[](unsigned idx) { return col[idx]; }

		//Overloads that directly effect a Mat3
		Mat4 &operator+=(const Mat4 &rhs) { return *this = Mat4{ col[0] + rhs.col[0], col[1] + rhs.col[1], col[2] + rhs.col[2], col[3] + rhs.col[3] }; }
		Mat4 &operator-=(const Mat4 &rhs) { return *this = Mat4{ col[0] - rhs.col[0], col[1] - rhs.col[1], col[2] - rhs.col[2], col[3] - rhs.col[3] }; }
		Mat4 &operator*=(const Mat4 &rhs) { return *this = Mat4{ col[0] * rhs.col[0], col[1] * rhs.col[1], col[2] * rhs.col[2], col[3] * rhs.col[3] }; }
		Mat4 &operator*=(float rhs) { return identity(); }

		//Creates an Identity Matrix for Mat3
		static Mat4 identity()
		{
			Mat4 r;
			r.col[0] = Vec4{ 1, 0, 0, 0 };
			r.col[1] = Vec4{ 0, 1, 0, 0 };
			r.col[2] = Vec4{ 0, 0, 1, 0 };
			r.col[3] = Vec4{ 0, 0, 0, 1 };
			return r;
		}

		Vec3 &up()  { return col[1].xyz; }
		Vec3 &right() { return col[0].xyz; }
		Vec3 &position() { return col[2].xyz; }

		Mat4  transpose() const;
		float determinant() const;
		Mat4  inverse() const;
	};

	bool operator==(const Mat4 &lhs, const Mat4 &rhs);
	bool operator!=(const Mat4 &lhs, const Mat4 &rhs);

	Mat4 operator+(const Mat4 &lhs, const Mat4 &rhs);
	Mat4 operator-(const Mat4 &lhs, const Mat4 &rhs);
	Mat4 operator*(const Mat4 &lhs, const Mat4 &rhs);
	Vec4 operator*(const Mat4 &lhs, const Vec4 &rhs);
	Mat4 operator*(const Mat4 &lhs, const float rhs);
	Mat4 operator*(const float lhs, const Mat4 &rhs);

	Mat4 rotate(float angle);
	Mat4 translate(const Vec3 &xyz);
	Mat4 scale(const Vec3 &xyz);

	std::ostream& operator<<(std::ostream &os, const Mat4 &output);
}