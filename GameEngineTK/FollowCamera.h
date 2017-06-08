//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@���@�ɒǏ]����J�����N���X
//
//���t�@2017/05/16
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#pragma once

#include "Camera.h"
#include <Keyboard.h>

#include "Player.h"

class FollowCamera : public Camera
{
public:
	static const float CAMERA_DISTANCE;		// �J�����Ǝ��@�̋���

	FollowCamera(int width, int height);
	~FollowCamera();

	// �X�V����
	void Update() override;

	// TPS���_�̏�����
	void InitializeTPS();

	// �Ǐ]�Ώۍ��W�̃Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	// �Ǐ]�Ώۊp�x�̃Z�b�g
	void SetTargetAngle(float targetAngle);

	// �L�[�{�[�h���Z�b�g����i���j
	void SetKeyboard(DirectX::Keyboard* keyboard);

	// �v���C���[�̃Z�b�g
	void SetPlayer(Player* player) { m_player = player; }

protected:
	DirectX::SimpleMath::Vector3 m_targetPos;	// �Ǐ]�Ώۂ̍��W
	float m_targetAngle;						// �Ǐ]�Ώۂ̊p�x

	// �L�[�{�[�h�i���j
	DirectX::Keyboard* m_keyboard;
	// �L�[�{�[�h�g���b�J�[�i���j
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	int m_keyflag;

	Player* m_player;
};