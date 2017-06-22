#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//==================================
//*ŠÖ”‚ÌŠT—v
//*ˆø”[Sphere,Sphere] ‹…AA‹…B
//*–ß‚è’l@true:“–‚½‚Á‚Ä‚¢‚é@false:“–‚½‚Á‚Ä‚¢‚È‚¢
//==================================
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// ’†SÀ•WŠÔ‚Ì·‚ğŒvZ
	Vector3 sub = sphereB.Center - sphereA.Center;
	// ’†SÀ•WŠÔ‚Ì‹——£‚ğŒvZ
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	// ”¼Œa‚Ì˜a
	float radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare* radiusSquare;

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}