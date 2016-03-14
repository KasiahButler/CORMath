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
		Vec3 &operator[](unsigned idx)       { return col[idx]; }

		//Overloads that directly effect a Mat3
		Mat3 &operator+=(const Mat3 &rhs) { return identity(); }
		Mat3 &operator-=(const Mat3 &rhs) { return identity(); }
		Mat3 &operator*=(const Mat3 &rhs) { return identity(); }
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

		Mat3 transpose() const;
		float determinant() const;
		Mat3 inverse() const;
		Mat3 OrthProj() const;
	};

	//Mat3 rotate   (float angle);
	//Mat3 translate(const Vec2 &xy);
	//Mat3 scale    (const Vec2 &xy);
}