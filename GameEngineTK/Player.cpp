#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Player::Player()
{
	m_timer = 0;

	m_angle = 0.0f;

	m_cycle = 0.0f;
	m_wingPcycle = 0.0f;
	m_wingNcycle = 0.0f;

	m_bulletFlag = false;

	m_keyboard = nullptr;

	m_clearFlag = false;
}


Player::~Player()
{

}

void Player::Initiarize()
{
	// �v���C���[�p�[�c�̃��[�h
	m_obj.resize(NUM);
	m_obj[FRFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[FLFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[BRFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[BLFOOT].LoadModel(L"Resources/foot.cmo");
	m_obj[BODY].LoadModel(L"Resources/body.cmo");
	m_obj[HEAD].LoadModel(L"Resources/head.cmo");
	m_obj[RWING].LoadModel(L"Resources/wing.cmo");
	m_obj[LWING].LoadModel(L"Resources/wing.cmo");
	m_obj[TAIL].LoadModel(L"Resources/tail.cmo");
	m_obj[STAR].LoadModel(L"Resources/star.cmo");
	m_obj[STAR2].LoadModel(L"Resources/star.cmo");

	m_clearPanel.LoadModel(L"Resources/clear.cmo");

	// �e�q�֌W������
	m_obj[FLFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[FRFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[BLFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[BRFOOT].SetObjParent(&m_obj[BODY]);
	m_obj[HEAD].SetObjParent(&m_obj[BODY]);
	m_obj[STAR].SetObjParent(&m_obj[BODY]);
	m_obj[STAR2].SetObjParent(&m_obj[BODY]);
	m_obj[RWING].SetObjParent(&m_obj[BODY]);
	m_obj[LWING].SetObjParent(&m_obj[BODY]);
	m_obj[TAIL].SetObjParent(&m_obj[BODY]);

	// �{�̂̈ʒu�̒���
	m_obj[BODY].SetScale(Vector3(1.0f, 1.0f, 0.7f));
	m_obj[BODY].SetRotation(Vector3(0.3f, 0.0f, 0.0f));
	m_obj[BODY].SetTranslation(Vector3(0.0f, 0.5f, 0.0f));

	// �e����̂���===
	// ���O��
	m_obj[FLFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[FLFOOT].SetRotation(Vector3(-0.8f, -0.3f, 0.0f));
	m_obj[FLFOOT].SetTranslation(Vector3(0.15f, -0.2f, -0.4f));
	// �E�O��
	m_obj[FRFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[FRFOOT].SetRotation(Vector3(-0.8f, 0.3f, 0.0f));
	m_obj[FRFOOT].SetTranslation(Vector3(-0.15f, -0.2f, -0.4f));
	// ����둫
	m_obj[BLFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[BLFOOT].SetRotation(Vector3(-0.8f, -0.3f, 0.0f));
	m_obj[BLFOOT].SetTranslation(Vector3(0.15f, -0.3f, 0.4f));
	// �E��둫
	m_obj[BRFOOT].SetScale(Vector3(0.5f, 0.8f, 0.9f));
	m_obj[BRFOOT].SetRotation(Vector3(-0.8f, 0.3f, 0.0f));
	m_obj[BRFOOT].SetTranslation(Vector3(-0.15f, -0.3f, 0.4f));
	// ��
	m_obj[HEAD].SetScale(Vector3(0.8f, 0.8f, 1.1f));
	m_obj[HEAD].SetRotation(Vector3(-0.2f, 0.0f, 0.0f));
	m_obj[HEAD].SetTranslation(Vector3(0.0f, 0.5f, -0.5f));
	// ������
	m_obj[TAIL].SetTranslation(Vector3(0.0f, 0.0f, 0.6f));
	// �E�͂�
	m_obj[RWING].SetScale(Vector3(1.0f, 1.0f, 0.8f));
	m_obj[RWING].SetRotation(Vector3(-0.5f, 0.3f, 0.0f));
	m_obj[RWING].SetTranslation(Vector3(0.3f, 0.3f, 0.0f));
	// ���͂�
	m_obj[LWING].SetScale(Vector3(1.0f, 1.0f, 0.8f));
	m_obj[LWING].SetRotation(Vector3(-0.5f, -0.3f, 0.0f));
	m_obj[LWING].SetTranslation(Vector3(-0.3f, 0.3f, 0.0f));
	// ��
	m_obj[STAR].SetScale(Vector3(2.0f, 2.0f, 2.0f));
	m_obj[STAR].SetTranslation(Vector3(0.0f, 1.0f, 0.0f));
	m_obj[STAR2].SetScale(Vector3(1.5f, 1.5f, 1.5f));
	m_obj[STAR2].SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	m_obj[STAR2].SetTranslation(Vector3(0.0f, 1.3f, -1.0f));

	// ��]�p�̏���ۑ�
	m_tailRota = m_obj[TAIL].GetRotation();
	m_RwingRota = m_obj[RWING].GetRotation();
	m_LwingRota = m_obj[LWING].GetRotation();

	// ����̂����蔻��m�[�h�ݒ�
	m_collisionNodeBullet.Initiarize();
	// ����p�[�c�ɂԂ牺����
	m_collisionNodeBullet.SetParent(&m_obj[STAR2]);
	// ����p�[�c����̃I�t�Z�b�g(����j
	m_collisionNodeBullet.SetTranslation(Vector3(0.0f, 0.0f, 0.0f));
	// �����蔻��̔��a
	m_collisionNodeBullet.SetLocalRadius(0.2f);

}

void Player::Update()
{
	m_angle += 0.1f;
	m_cycle += 0.05f;
	m_wingPcycle += 0.1;
	m_wingNcycle -= 0.1;

	// �L�[�{�[�h�̏�Ԃ��擾����
	Keyboard::State key = m_keyboard->GetState();
	m_keyboardTracker.Update(key);

	if (key.A)
	{
		float angleX = m_obj[BODY].GetRotation().x;
		float angleY = m_obj[BODY].GetRotation().y;
		m_obj[BODY].SetRotation(Vector3(angleX, angleY + 0.03f, 0.0f));
	}
	if (key.D)
	{
		float angleX = m_obj[BODY].GetRotation().x;
		float angleY = m_obj[BODY].GetRotation().y;
		m_obj[BODY].SetRotation(Vector3(angleX, angleY - 0.03f, 0.0f));
	}

	if (key.W)
	{
		// �ړ��x�N�g��
		Vector3 move(0.0f, 0.0f, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]������===========
		// ��]�s����ړ��x�N�g���ɂ�����
		float angle = m_obj[BODY].GetRotation().y;
		Matrix rotation = Matrix::CreateRotationY(angle);
		move = Vector3::TransformNormal(move, rotation);
		// ���@�̍��W���ړ�
		m_pos = m_obj[BODY].GetTranslation();
		m_pos += move;
		m_obj[BODY].SetTranslation(m_pos);
	}
	if (key.S)
	{
		// �ړ��x�N�g��
		Vector3 move(0, 0, 0.1f);
		// ��]�s��
		float angle = m_obj[BODY].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		move = Vector3::TransformNormal(move, rotmat);
		// ���@�̍��W���ړ�
		m_pos = m_obj[BODY].GetTranslation();
		m_pos += move;
		m_obj[BODY].SetTranslation(m_pos);
	}

	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::Space) && !m_bulletFlag)
	{
		fireBullet();
	}

	//// �����̏㉺�̓���
	//m_pos.y = (0.5f * sinf(m_cycle)) + 1.0f;
	//m_obj[BODY].SetTranslation(m_pos);

	// �����ۂ̉�]
	m_tailRota.z += 0.5f;
	m_obj[TAIL].SetRotation(m_tailRota);

	// �H���̓���
	m_RwingRota.y = (0.3f * sinf(m_wingPcycle)) + 0.4;
	m_obj[RWING].SetRotation(m_RwingRota);

	m_LwingRota.y = (0.3f * sinf(m_wingNcycle)) - 0.4;
	m_obj[LWING].SetRotation(m_LwingRota);

	// ���̓���
	m_obj[STAR].SetRotation(Vector3(0.0f, m_cycle, m_cycle));
	m_obj[STAR].SetTranslation(Vector3(cosf(m_cycle), (sinf(m_cycle + m_cycle)) + 0.5f, 0.0f));

	if (m_bulletFlag)
	{
		Vector3 pos = m_obj[STAR2].GetTranslation();
		pos += m_bulletVel;
		m_obj[STAR2].SetTranslation(pos);

		m_timer++;

		if (m_timer % 120 == 0)
		{
			resetBullet();
		}

	}
	//else
	//{
	//	m_obj[STAR2].SetRotation(Vector3(0.0f, m_angle, 0.0f));
	//}

	Calc();
}

void Player::Rebder()
{
	// �v���C���̕`��
	for (std::vector<Obj3D>::iterator it = m_obj.begin(); it != m_obj.end(); it++)
	{
		it->Obj3D::Render();
	}

	if (m_clearFlag)
	{
		m_clearPanel.SetObjParent(&m_obj[BODY]);
		m_clearPanel.SetScale(Vector3(0.3f, 0.3f, 0.3f));
		m_clearPanel.SetRotation(Vector3(-0.2f, 0.0f, 0.0f));
		m_clearPanel.SetTranslation(Vector3(0.0f, 3.0f, 0.0f));
		m_clearPanel.DisableLighting();
		m_clearPanel.Render();
	}
	m_collisionNodeBullet.Render();
}

void Player::Calc()
{
	for (std::vector<Obj3D>::iterator it = m_obj.begin();
		it != m_obj.end();
		it++)
	{
		it->Obj3D::Update();
	}

	m_clearPanel.Update();

	m_collisionNodeBullet.Updete();
}

void Player::fireBullet()
{
	if (m_bulletFlag)
	{
		return;
	}

	// ���[���h�s����擾
	Matrix worldm = m_obj[STAR2].GetWorld();

	Vector3 scale;			// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

	// ���[���h�s�񂩂�e�v�f�����o��
	worldm.Decompose(scale, rotation, translation);

	// �e�q���֌W���������ăp�[�c��Ɨ�������
	m_obj[STAR2].SetObjParent(nullptr);
	m_obj[STAR2].SetScale(scale);
	m_obj[STAR2].SetRotationQ(rotation);
	m_obj[STAR2].SetTranslation(translation);

	m_bulletVel = Vector3(0.0f,-0.05f, -0.15f);

	m_bulletVel = Vector3::Transform(m_bulletVel, rotation);

	m_bulletFlag = true;
}

void Player::resetBullet()
{
	if (!m_bulletFlag)
	{
		return;
	}

	m_timer = 0;

	m_obj[STAR2].SetObjParent(&m_obj[BODY]);

	m_obj[STAR2].SetScale(Vector3(1.5f, 1.5f, 1.5f));
	m_obj[STAR2].SetRotation(Vector3(0,0,0));
	m_obj[STAR2].SetTranslation(Vector3(0.0f, 1.3f, -1.0f));

	m_obj[STAR2].Update();

	m_bulletVel = Vector3::Zero;

	m_bulletFlag = false;
}

void Player::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}