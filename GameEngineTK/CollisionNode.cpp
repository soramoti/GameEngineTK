#include "pch.h"
#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// CollisionNodeのメンバ関数
void CollisionNode::SetParent(Obj3D * parent)
{
	m_obj.SetObjParent(parent);
}


// SphereNOdeのメンバ関数
SphereNode::SphereNode()
{
	// デフォルト半径
	Radius = 1.0f;
}

void SphereNode::Initiarize()
{
	m_obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Updete()
{
	m_obj.SetTranslation(m_translation);
	m_obj.SetScale(Vector3(m_localRadius));

	m_obj.Update();

	// 判定球の要素を計算
	const Matrix& worldm = m_obj.GetWorld();
	// モデル座標系での中心点
	Vector3 center(0, 0, 0);
	Vector3 right(1,0,0);
	// ワールド座標に変換
	center = Vector3::Transform(center, worldm);
	right = Vector3::Transform(right, worldm);
	// 判定球の要素を代入
	Sphere::Center = center;
	Sphere::Radius = Vector3::Distance(center, right);
}

void SphereNode::Render()
{
	m_obj.Render();
}