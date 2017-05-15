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
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	// �Ǐ]�J����====
	Vector3 eyepos, refpos;
	// ���@�̏��2m�̈ʒu���Ƃ炦��
	refpos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);
	// �Q�Ɠ_���王�_�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	// 
	Matrix rotation = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	// �����x�N�g������]
	cameraV = Vector3::TransformNormal(cameraV, rotation);
	// ���_���W���v�Z
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);

	// ���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}
