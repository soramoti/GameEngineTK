#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;		// �J�����Ǝ��@�̋���

FollowCamera::FollowCamera(int width, int height)
	: Camera(width,height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	m_keyflag = 0;
	InitializeTPS();
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	// �L�[�{�[�h�̏�Ԃ��擾�i���j
	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboardTracker.Update(keystate);

	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		// �t���O��؂�ւ�
		m_keyflag = (m_keyflag + 1) % 2;
		if (m_keyflag == 0)
		{
			InitializeTPS();
		}
	}

	// �Ǐ]�Ώۂ̍��W�̐ݒ�
	SetTargetPos(m_player->GetPos());
	SetTargetAngle(m_player->GetAngle().y);


	if (m_keyflag == 0)
	{
		 //TPS���_=====
		// ���@�̏��(2m)�̈ʒu���Ƃ炦��
		refpos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);
		// �Q�Ɠ_���王�_�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
		// ���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rotation = Matrix::CreateRotationY(m_targetAngle);
		// �����x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotation);
		// ���_���W���v�Z
		eyepos = refpos + cameraV;

		// ���_�����݈ʒu������
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.1f;
		// �Q�Ɠ_�����݈ʒu������
		refpos = m_refpos + (refpos - m_refpos) * 0.1f;
	}
	else
	{
		// FPS���_=====
		Vector3 upEyepos;
		// ���@�̏���̈ʒu�ɃJ������u��
		upEyepos = m_targetPos + Vector3(0.0f, 0.2f, 0.0f);
		// �Q�Ɠ_���王�_�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
		// ���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rotation = Matrix::CreateRotationY(m_targetAngle);
		// �����x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotation);
		eyepos = upEyepos + cameraV * 0.1f;
		// �Q�Ɠ_���W���v�Z
		refpos = eyepos + cameraV;
	}


	SetEyePos(eyepos);
	SetRefPos(refpos);

	// ���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	//TPS���_=====
	// ���@�̏��(2m)�̈ʒu���Ƃ炦��
	refpos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);
	// �Q�Ɠ_���王�_�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	// ���@�̌��ɉ�荞�ނ��߂̉�]
	Matrix rotation = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	// �����x�N�g������]
	cameraV = Vector3::TransformNormal(cameraV, rotation);
	// ���_���W���v�Z
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
