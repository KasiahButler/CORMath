#include "Matrix3.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>

int main()
{
	COR::Mat3 a{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	COR::Mat3 b{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	COR::Mat3 c = a - b;

	std::cout << c << std::endl;

	system("pause");
}