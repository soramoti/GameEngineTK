#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//==================================
//*�֐��̊T�v
//*����[Sphere,Sphere] ��A�A��B
//*�߂�l�@true:�������Ă���@false:�������Ă��Ȃ�
//==================================
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// ���S���W�Ԃ̍����v�Z
	Vector3 sub = sphereB.Center - sphereA.Center;
	// ���S���W�Ԃ̋������v�Z
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	// ���a�̘a
	float radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare* radiusSquare;

	// ���������a�̘a���傫����΁A�������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}