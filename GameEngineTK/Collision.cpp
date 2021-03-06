#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//==================================
//*関数の概要
//*引数[Sphere,Sphere] 球A、球B
//*戻り値　true:当たっている　false:当たっていない
//==================================
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// 中心座標間の差を計算
	Vector3 sub = sphereB.Center - sphereA.Center;
	// 中心座標間の距離を計算
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	// 半径の和
	float radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare* radiusSquare;

	// 距離が半径の和より大きければ、当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}