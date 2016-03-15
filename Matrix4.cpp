#include "Matrix4.h"

namespace COR
{
	//Transpose Mat4
	Mat4  Mat4::transpose() const
	{
		Mat4 hold;
		hold.col[0] = { m[0][0], m[1][0], m[2][0], m[3][0] };
		hold.col[1] = { m[0][1], m[1][1], m[2][1], m[3][1] };
		hold.col[2] = { m[0][2], m[1][2], m[2][2], m[3][2] };
		hold.col[3] = { m[0][3], m[1][3], m[2][3], m[3][3] };
		return hold;
	}

	//Relational Operator Overloads for Mat4
	bool operator==(const Mat4 &lhs, const Mat4 &rhs)
	{
		if (lhs.col[0] == rhs.col[0] && lhs.col[1] == rhs.col[1] && lhs.col[2] == rhs.col[2] && lhs.col[3] == rhs.col[3]) { return true; }
		return false;
	}

	bool operator!=(const Mat4 &lhs, const Mat4 &rhs)
	{
		if (lhs == rhs) { return false; }
		return true;
	}

	//Math Operator Overloads for Mat4
	Mat4 operator+(const Mat4 &lhs, const Mat4 &rhs)
	{
		return{ lhs.col[0] + rhs.col[0], lhs.col[1] + rhs.col[1], lhs.col[2] + rhs.col[2], lhs.col[3] + rhs.col[3] };
	}

	Mat4 operator-(const Mat4 &lhs, const Mat4 &rhs)
	{
		return{ lhs.col[0] - rhs.col[0], lhs.col[1] - rhs.col[1], lhs.col[2] - rhs.col[2], lhs.col[3] - rhs.col[3] };
	}

	Mat4 operator*(const Mat4 &lhs, const Mat4 &rhs)
	{
		Mat4 lhsT = lhs.transpose();

		return{ dot(lhsT.col[0], rhs.col[0]), dot(lhsT.col[1], rhs.col[0]), dot(lhsT.col[2], rhs.col[0]), dot(lhsT.col[3], rhs.col[0]),
			    dot(lhsT.col[0], rhs.col[1]), dot(lhsT.col[1], rhs.col[1]), dot(lhsT.col[2], rhs.col[1]), dot(lhsT.col[3], rhs.col[1]),
			    dot(lhsT.col[0], rhs.col[2]), dot(lhsT.col[1], rhs.col[2]), dot(lhsT.col[2], rhs.col[2]), dot(lhsT.col[3], rhs.col[2]),
				dot(lhsT.col[0], rhs.col[3]), dot(lhsT.col[1], rhs.col[3]), dot(lhsT.col[2], rhs.col[3]), dot(lhsT.col[3], rhs.col[3]) };
	}

	Vec4 operator*(const Mat4 &lhs, const Vec4 &rhs)
	{
		Mat4 lhsT = lhs.transpose();

		return{ dot(lhsT.col[0], rhs), dot(lhsT.col[1], rhs), dot(lhsT.col[2], rhs), dot(lhsT.col[3], rhs) };
	}

	Mat4 operator*(const Mat4 &lhs, float rhs)
	{
		return{ lhs.col[0] * rhs, lhs.col[1] * rhs, lhs.col[2] * rhs, lhs.col[3] * rhs };
	}

	Mat4 operator*(float lhs, const Mat4 &rhs)
	{
		return rhs * lhs;
	}

	//Mat4 Rotate, Translate, Scale Functions
	Mat4 rotateX(float angle)
	{
		Mat4 hold;
		hold.col[0] = { 0, 0, 0, 0 };
		hold.col[1] = { 0, cosf(angle), sinf(angle), 0 };
		hold.col[2] = { 0, -sinf(angle), cosf(angle), 0 };
		hold.col[3] = { 0, 0, 0, 0 };
		return hold;
	}

	Mat4 rotateY(float angle)
	{
		Mat4 hold;
		hold.col[0] = { cosf(angle), 0, 0, sinf(angle) };
		hold.col[1] = { 0, 0, 0, 0 };
		hold.col[2] = { 0, 0, 0, 0 };
		hold.col[3] = { -sinf(angle), 0, 0, cosf(angle) };
		return hold;
	}

	Mat4 rotateZ(float angle)
	{
		Mat4 hold;
		hold.col[0] = { cosf(angle), -sinf(angle), 0, 0 };
		hold.col[1] = { sinf(angle), cosf(angle), 0, 0 };
		hold.col[2] = { 0, 0, 0, 0 };
		hold.col[3] = { 0, 0, 0, 0 };
		return hold;
	}

	Mat4 translate(const Vec3 &xyz)
	{
		Mat4 hold;
		hold.col[3] = { xyz.x, xyz.y, xyz.z, 0 };
		return hold;
	}

	Mat4 scale(const Vec3 &xyz)
	{
		Mat4 hold;
		hold.m[0][0] = xyz.x;
		hold.m[1][1] = xyz.y;
		hold.m[2][2] = xyz.z;
		return hold;
	}

	//Output Operator Overload for Mat4
	std::ostream& operator<<(std::ostream &os, const Mat4 &output)
	{
		os << output.m[0][0] << " " << output.m[1][0] << " " << output.m[2][0] << output.m[3][0] << std::endl;
		os << output.m[0][1] << " " << output.m[1][1] << " " << output.m[2][1] << output.m[3][1] << std::endl;
		os << output.m[0][2] << " " << output.m[1][2] << " " << output.m[2][2] << output.m[3][2] << std::endl;
		os << output.m[0][3] << " " << output.m[1][3] << " " << output.m[2][3] << output.m[3][3] << std::endl;
		return os;
	}
}