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

		//Overload to allow direct access to a location in Vec4 Array
		Vec4  operator[](unsigned idx) const { return col[idx]; }
		Vec4 &operator[](unsigned idx) { return col[idx]; }

		//Overloads that directly effect a Mat4
		Mat4 &operator+=(const Mat4 &rhs) { return *this = Mat4{ col[0] + rhs.col[0], col[1] + rhs.col[1], col[2] + rhs.col[2], col[3] + rhs.col[3] }; }
		Mat4 &operator-=(const Mat4 &rhs) { return *this = Mat4{ col[0] - rhs.col[0], col[1] - rhs.col[1], col[2] - rhs.col[2], col[3] - rhs.col[3] }; }
		Mat4 &operator*=(const Mat4 &rhs) { return *this = Mat4{ col[0] * rhs.col[0], col[1] * rhs.col[1], col[2] * rhs.col[2], col[3] * rhs.col[3] }; }
		Mat4 &operator*=(float rhs) { return *this = Mat4{ col[0] * rhs, col[1] * rhs, col[2] * rhs, col[3] * rhs }; }

		//Creates an Identity Matrix for Mat4
		static Mat4 identity()
		{
			Mat4 r;
			r.col[0] = Vec4{ 1, 0, 0, 0 };
			r.col[1] = Vec4{ 0, 1, 0, 0 };
			r.col[2] = Vec4{ 0, 0, 1, 0 };
			r.col[3] = Vec4{ 0, 0, 0, 1 };
			return r;
		}

		//Get Directions for Mat4
		Vec3 &up()  { return col[1].xyz; }
		Vec3 &right() { return col[0].xyz; }
		Vec3 &position() { return col[2].xyz; }

		//Rotates the Mat4
		Mat4  transpose() const;

		//Need to come back and finish these when I have time
		//float determinant() const;
		//Mat4  inverse() const;
	};

	//Relational Operators
	bool operator==(const Mat4 &lhs, const Mat4 &rhs);
	bool operator!=(const Mat4 &lhs, const Mat4 &rhs);

	//Math Operators
	Mat4 operator+(const Mat4 &lhs, const Mat4 &rhs);
	Mat4 operator-(const Mat4 &lhs, const Mat4 &rhs);
	Mat4 operator*(const Mat4 &lhs, const Mat4 &rhs);
	Vec4 operator*(const Mat4 &lhs, const Vec4 &rhs);
	Mat4 operator*(const Mat4 &lhs, const float rhs);
	Mat4 operator*(const float lhs, const Mat4 &rhs);

	//Modification Matrices
	Mat4 rotateX(float angle);
	Mat4 rotateY(float angle);
	Mat4 rotateZ(float angle);
	Mat4 translate(const Vec3 &xyz);
	Mat4 scale(const Vec3 &xyz);

	//Output Overload for Mat4
	std::ostream& operator<<(std::ostream &os, const Mat4 &output);
}