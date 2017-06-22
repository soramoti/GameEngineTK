#include "pch.h"
#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// CollisionNode�̃����o�֐�
void CollisionNode::SetParent(Obj3D * parent)
{
	m_obj.SetObjParent(parent);
}


// SphereNOde�̃����o�֐�
SphereNode::SphereNode()
{
	// �f�t�H���g���a
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

	// ���苅�̗v�f���v�Z
	const Matrix& worldm = m_obj.GetWorld();
	// ���f�����W�n�ł̒��S�_
	Vector3 center(0, 0, 0);
	Vector3 right(1,0,0);
	// ���[���h���W�ɕϊ�
	center = Vector3::Transform(center, worldm);
	right = Vector3::Transform(right, worldm);
	// ���苅�̗v�f����
	Sphere::Center = center;
	Sphere::Radius = Vector3::Distance(center, right);
}

void SphereNode::Render()
{
	m_obj.Render();
}