//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@���@�ɒǏ]����J�����N���X�̃w�b�_
//
//���t�@
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	static const float CAMERA_DISTANCE;		// �J�����Ǝ��@�̋���

	FollowCamera(int width, int height);
	~FollowCamera();

	// �X�V����
	void Update() override;

	// �Ǐ]�Ώۍ��W�̃Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	// �Ǐ]�Ώۊp�x�̃Z�b�g
	void SetTargetAngle(float targetAngle);

protected:
	DirectX::SimpleMath::Vector3 m_targetPos;	// �Ǐ]�Ώۂ̍��W
	float m_targetAngle;						// �Ǐ]�Ώۂ̊p�x
};