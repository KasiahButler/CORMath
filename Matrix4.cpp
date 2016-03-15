#include "Matrix4.h"

namespace COR
{
	Mat4  Mat4::transpose() const
	{
		Mat4 hold;
		hold.col[0] = { m[0][0], m[1][0], m[2][0], m[3][0] };
		hold.col[1] = { m[0][1], m[1][1], m[2][1], m[3][1] };
		hold.col[2] = { m[0][2], m[1][2], m[2][2], m[3][2] };
		hold.col[3] = { m[0][3], m[1][3], m[2][3], m[3][3] };
		return hold;
	}
}