#pragma once
#include <iostream>
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
		Mat3 &operator*=(float rhs) { return *this = Mat3{ col[0] * rhs, col[1] * rhs, col[2] * rhs }; }

		//Creates an Identity Matrix for Mat3
		static Mat3 identity()
		{
			Mat3 r;
			r.col[0] = Vec3{ 1, 0, 0 };
			r.col[1] = Vec3{ 0, 1, 0 };
			r.col[2] = Vec3{ 0, 0, 1 };
			return r;
		}

		//Gets Mat3 Directions
		Vec2 &up()       { return col[1].xy; }
		Vec2 &right()    { return col[0].xy; }
		Vec2 &position() { return col[2].xy; }
		 
		//Functions to rotate and find Inverse of a Mat3
		Mat3  transpose() const;
		float determinant() const;
		Mat3  inverse() const;
	};

	//Relational Operators
	bool operator==(const Mat3 &lhs, const Mat3 &rhs);
	bool operator!=(const Mat3 &lhs, const Mat3 &rhs);

	//Math Operators
	Mat3 operator+(const Mat3 &lhs, const Mat3 &rhs);
	Mat3 operator-(const Mat3 &lhs, const Mat3 &rhs);
	Mat3 operator*(const Mat3 &lhs, const Mat3 &rhs);
	Vec3 operator*(const Mat3 &lhs, const Vec3 &rhs);
	Mat3 operator*(const Mat3 &lhs, const float rhs);
	Mat3 operator*(const float lhs, const Mat3 &rhs);

	//Transformation Matrices
	Mat3 rotate(float angle);
	Mat3 translate(const Vec2 &xy);
	Mat3 scale(const Vec2 &xy);

	//Mat3 Output Overloads
	std::ostream& operator<<(std::ostream &os, const Mat3 &output);
}