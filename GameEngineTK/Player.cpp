#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Player::Player()
{
	m_angle = 0.0f;

	m_cycle = 0.0f;
	m_wingPcycle = 0.0f;
	m_wingNcycle = 0.0f;

	m_keyboard = nullptr;

}


Player::~Player()
{

}

void Player::Initiarize()
{
	// �v���C���[�p�[�c�̃��[�h
	m_objPlayer.resize(NUM);
	m_objPlayer[FRFOOT].LoadModel(L"Resources/foot.cmo");
	m_objPlayer[FLFOOT].LoadModel(L"Resources/foot.cmo");
	m_objPlayer[BRFOOT].LoadModel(L"Resources/foot.cmo");
	m_objPlayer[BLFOOT].LoadModel(L"Resources/foot.cmo");
	m_objPlayer[BODY].LoadModel(L"Resources/body.cmo");
	m_objPlayer[HEAD].LoadModel(L"Resources/head.cmo");
	m_objPlayer[RWING].LoadModel(L"Resources/wing.cmo");
	m_objPlayer[LWING].LoadModel(L"Resources/wing.cmo");
	m_objPlayer[TAIL].LoadModel(L"Resources/tail.cmo");
	m_objPlayer[STAR].LoadModel(L"Resources/star.cmo");

	// �e�q�֌W������
	m_objPlayer[FLFOOT].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[FRFOOT].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[BLFOOT].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[BRFOOT].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[HEAD].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[STAR].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[RWING].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[LWING].SetObjParent(&m_objPlayer[BODY]);
	m_objPlayer[TAIL].SetObjParent(&m_objPlayer[BODY]);

	// �{�̂̈ʒu�̒���
	m_objPlayer[BODY].SetScale(Vector3(1.0f, 1.0f, 0.7f));
	m_objPlayer[BODY].SetRotation(Vector3(0.3f, 0.0f, 0.0f));
	m_objPlayer[BODY].SetTransration(Vector3(0.0f, 5.0f, 0.0f));

	// �e����̂���===
	// ���O��
	m_objPlayer[FLFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_objPlayer[FLFOOT].SetRotation(Vector3(-0.8f, -0.3f, 0.0f));
	m_objPlayer[FLFOOT].SetTransration(Vector3(0.15f, -0.2f, -0.4f));
	// �E�O��
	m_objPlayer[FRFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_objPlayer[FRFOOT].SetRotation(Vector3(-0.8f, 0.3f, 0.0f));
	m_objPlayer[FRFOOT].SetTransration(Vector3(-0.15f, -0.2f, -0.4f));
	// ����둫
	m_objPlayer[BLFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_objPlayer[BLFOOT].SetRotation(Vector3(-0.8f, -0.3f, 0.0f));
	m_objPlayer[BLFOOT].SetTransration(Vector3(0.15f, -0.3f, 0.4f));
	// �E��둫
	m_objPlayer[BRFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_objPlayer[BRFOOT].SetRotation(Vector3(-0.8f, 0.3f, 0.0f));
	m_objPlayer[BRFOOT].SetTransration(Vector3(-0.15f, -0.3f, 0.4f));
	// ��
	m_objPlayer[HEAD].SetScale(Vector3(0.8f, 0.8f, 1.1f));
	m_objPlayer[HEAD].SetRotation(Vector3(-0.2f, 0.0f, 0.0f));
	m_objPlayer[HEAD].SetTransration(Vector3(0.0f, 0.5f, -0.5f));
	// ������
	m_objPlayer[TAIL].SetTransration(Vector3(0.0f, 0.0f, 0.6f));
	// �E�͂�
	m_objPlayer[RWING].SetScale(Vector3(1.0f, 1.0f, 0.8f));
	m_objPlayer[RWING].SetRotation(Vector3(-0.5f, 0.3f, 0.0f));
	m_objPlayer[RWING].SetTransration(Vector3(0.3f, 0.3f, 0.0f));
	// ���͂�
	m_objPlayer[LWING].SetScale(Vector3(1.0f, 1.0f, 0.8f));
	m_objPlayer[LWING].SetRotation(Vector3(-0.5f, -0.3f, 0.0f));
	m_objPlayer[LWING].SetTransration(Vector3(-0.3f, 0.3f, 0.0f));
	// ��
	m_objPlayer[STAR].SetScale(Vector3(2.0f, 2.0f, 2.0f));
	m_objPlayer[STAR].SetTransration(Vector3(0.0f, 1.0f, 0.0f));

	// ��]�p�̏���ۑ�
	m_tailRota = m_objPlayer[TAIL].GetRotation();
	m_RwingRota = m_objPlayer[RWING].GetRotation();
	m_LwingRota = m_objPlayer[LWING].GetRotation();

}

void Player::Update()
{
	m_angle += 0.05f;
	m_cycle += 0.05;
	m_wingPcycle += 0.1;
	m_wingNcycle -= 0.1;

	// �L�[�{�[�h�̏�Ԃ��擾����
	Keyboard::State key = m_keyboard->GetState();

	if (key.A)
	{
		float angleX = m_objPlayer[BODY].GetRotation().x;
		float angleY = m_objPlayer[BODY].GetRotation().y;
		m_objPlayer[BODY].SetRotation(Vector3(angleX, angleY + 0.03f, 0.0f));
	}
	if (key.D)
	{
		float angleX = m_objPlayer[BODY].GetRotation().x;
		float angleY = m_objPlayer[BODY].GetRotation().y;
		m_objPlayer[BODY].SetRotation(Vector3(angleX, angleY - 0.03f, 0.0f));
	}

	if (key.W)
	{
		// �ړ��x�N�g��
		Vector3 move(0.0f, 0.0f, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]������===========
		// ���[���h�s����ړ��x�N�g���ɂ�����
		//move = Vector3::TransformNormal(move, m_worldRobbot);
		// ��]�s����ړ��x�N�g���ɂ�����
		float angle = m_objPlayer[BODY].GetRotation().y;
		Matrix rotation = Matrix::CreateRotationY(angle);
		move = Vector3::TransformNormal(move, rotation);
		// ���@�̍��W���ړ�
		m_pos = m_objPlayer[BODY].GetTransration();
		m_pos += move;
		m_objPlayer[BODY].SetTransration(m_pos);
	}
	if (key.S)
	{
		// �ړ��x�N�g��
		Vector3 move(0, 0, 0.1f);
		// ��]�s��
		float angle = m_objPlayer[BODY].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		move = Vector3::TransformNormal(move, rotmat);
		// ���@�̍��W���ړ�
		m_pos = m_objPlayer[BODY].GetTransration();
		m_pos += move;
		m_objPlayer[BODY].SetTransration(m_pos);
	}

	// �����̏㉺�̓���
	m_pos.y = (0.5f * sinf(m_cycle)) + 1.0f;
	m_objPlayer[BODY].SetTransration(m_pos);

	// �����ۂ̉�]
	m_tailRota.z += 0.5f;
	m_objPlayer[TAIL].SetRotation(m_tailRota);

	// �H���̓���
	m_RwingRota.y = (0.3f * sinf(m_wingPcycle)) + 0.4;
	m_objPlayer[RWING].SetRotation(m_RwingRota);

	m_LwingRota.y = (0.3f * sinf(m_wingNcycle)) - 0.4;
	m_objPlayer[LWING].SetRotation(m_LwingRota);

	// ���̓���
	m_objPlayer[STAR].SetRotation(Vector3(0.0f, m_angle, m_cycle));
	m_objPlayer[STAR].SetTransration(Vector3(cosf(m_cycle), (sinf(m_cycle + m_cycle)) + 0.5f, 0.0f));


	for (std::vector<Obj3D>::iterator it = m_objPlayer.begin();
		it != m_objPlayer.end();
		it++)
	{
		it->Obj3D::Update();
	}

}

void Player::Rebder()
{
	// �v���C���̕`��
	for (std::vector<Obj3D>::iterator it = m_objPlayer.begin(); it != m_objPlayer.end(); it++)
	{
		it->Obj3D::Render();
	}

}

void Player::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}