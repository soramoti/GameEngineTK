//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@�����蔻��m�[�h
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#pragma once

#include "Collision.h"
#include "Obj3D.h"

// �����蔻��m�[�h
class CollisionNode
{
public:
	virtual void Initiarize() = 0;
	virtual void Updete() = 0;
	virtual void Render() = 0;
	// �e���Z�b�g
	void SetParent(Obj3D* parent);
	// �e����̃I�t�Z�b�g���Z�b�g
	void SetTranslation(const DirectX::SimpleMath::Vector3& trans) { m_translation = trans; }

	// �f�o�b�O�\����ON/OFF��ݒ�
	static void SetDebugVisible(bool flag) { m_DebugVisible = flag; }
	// �f�o�b�O�\����ON/OFF���擾
	static bool GetDebugVisible(void) { return m_DebugVisible; }
private:
	// �f�o�b�O�\����ON/OFF�t���O
	static bool m_DebugVisible;
protected:
	// �f�o�b�N�\���I�u�W�F�N�g
	Obj3D m_obj;
	// �e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_translation;
};


// �����蔻�苅�m�[�h
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	void Initiarize();
	void Updete();
	void Render();
	// ���[�J�����a���Z�b�g
	void SetLocalRadius(float radus) { m_localRadius = radus; }
protected:
	// ���[�J�����a
	float m_localRadius;

};

