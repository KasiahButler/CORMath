#include "Matrix3.h"

namespace COR
{
	//Transpose a Mat3
	Mat3 Mat3::transpose() const
	{
		Mat3 hold;
		hold[0] = { m[0][0], m[1][0], m[2][0] };
		hold[1] = { m[0][1], m[1][1], m[2][1] };
		hold[2] = { m[0][2], m[1][2], m[2][2] };
		return hold;
	}

	//Functions for finding Mat3 Inverse
	float Mat3::determinant() const
	{
		return (m[0][0] * m[1][1] * m[2][2])
			 + (m[0][1] * m[1][2] * m[2][0])
			 + (m[0][2] * m[1][0] * m[2][1])
			 - (m[0][1] * m[1][0] * m[2][2]) 
			 - (m[0][0] * m[1][2] * m[2][1]) 
			 - (m[0][2] * m[1][1] * m[2][0]);
	}

	Mat3 Mat3::inverse() const
	{
		Mat3 hold = { m[1][1] * m[2][2] - m[2][1] * m[1][2], m[2][1] * m[0][2] - m[0][1] * m[2][2], m[0][1] * m[1][2] - m[1][1] * m[0][2],
					  m[2][0] * m[1][2] - m[1][0] * m[2][2], m[0][0] * m[2][2] - m[2][0] * m[0][2], m[1][0] * m[0][2] - m[0][0] * m[1][2], 
					  m[1][0] * m[2][1] - m[2][0] * m[1][1], m[2][0] * m[0][1] - m[0][0] * m[2][1], m[0][0] * m[1][1] - m[1][0] * m[0][1] };

	    return hold * (1 / determinant());
	}

	//Relational Operator Overloads for Mat3
	bool operator==(const Mat3 &lhs, const Mat3 &rhs)
	{
		if (lhs.col[0] == rhs.col[0] && lhs.col[1] == rhs.col[1] && lhs.col[2] == rhs.col[2]) { return true; }
		else { return false; }
	}

	bool operator!=(const Mat3 &lhs, const Mat3 &rhs)
	{
		if (lhs == rhs) { return false; }
		else { return true; }
	}

	//Math Operator Overloads for Mat3
	Mat3 operator+(const Mat3 &lhs, const Mat3 &rhs)
	{
		return{ lhs.col[0] + rhs.col[0], lhs.col[1] + rhs.col[1], lhs.col[2] + rhs.col[2] };
	}

	Mat3 operator-(const Mat3 &lhs, const Mat3 &rhs)
	{
		return{ lhs.col[0] - rhs.col[0], lhs.col[1] - rhs.col[1], lhs.col[2] - rhs.col[2] };
	}

	Mat3 operator*(const Mat3 &lhs, const Mat3 &rhs)
	{
		Mat3 lhsT = lhs.transpose();

		return{ dot(lhsT.col[0], rhs.col[0]), dot(lhsT.col[1], rhs.col[0]), dot(lhsT.col[2], rhs.col[0]),
				dot(lhsT.col[0], rhs.col[1]), dot(lhsT.col[1], rhs.col[1]), dot(lhsT.col[2], rhs.col[1]),
				dot(lhsT.col[0], rhs.col[2]), dot(lhsT.col[1], rhs.col[2]), dot(lhsT.col[2], rhs.col[2]) };
	}

	Vec3 operator*(const Mat3 &lhs, const Vec3 &rhs) 
	{
		Mat3 lhsT = lhs.transpose();

		return{ dot(lhsT.col[0], rhs), dot(lhsT.col[1], rhs), dot(lhsT.col[2], rhs) };
	}

	Mat3 operator*(const Mat3 &lhs, float rhs) 
	{
		return{ lhs.col[0] * rhs, lhs.col[1] * rhs, lhs.col[2] * rhs };
	}

	Mat3 operator*(float lhs, const Mat3 &rhs) 
	{
		return rhs * lhs;
	}

	//Rotation, Translate, and Scale Functions
	Mat3 rotate(float angle) 
	{ 
		Mat3 hold = Mat3::identity();
		hold.col[0] = Vec3{ cosf(angle), sinf(angle), 0 };
		hold.col[1] = Vec3{ -sinf(angle), cosf(angle), 0 };
		return hold;
	}

	Mat3 translate(const Vec2 &xy) 
	{
		Mat3 hold = Mat3::identity();
		hold.m[2][0] = xy.x;
		hold.m[2][1] = xy.y;
		return hold;
	}

	Mat3 scale(const Vec2 &xy) 
	{
		Mat3 hold = Mat3::identity();
		hold.m[0][0] = xy.x;
		hold.m[1][1] = xy.y;
		return hold;
	}

	//Output Stream Overload for Mat3
	std::ostream& operator<<(std::ostream &os, const Mat3 &output)
	{
		os << output.m[0][0] << " " << output.m[1][0] << " " << output.m[2][0] << std::endl;
		os << output.m[0][1] << " " << output.m[1][1] << " " << output.m[2][1] << std::endl;
		os << output.m[0][2] << " " << output.m[1][2] << " " << output.m[2][2] << std::endl;
		return os;
	}
}
