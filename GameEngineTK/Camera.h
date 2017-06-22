//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@�J�����𐧌䂷��N���X�w�b�_
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	// �X�V����
	virtual void Update();

	// �r���[�s����擾
	const DirectX::SimpleMath::Matrix& GetVeiw();
	// �ˉe�s����擾
	const DirectX::SimpleMath::Matrix& GetProj();

	// ���_���W���Z�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	// �����_/�Q�Ɠ_���Z�b�g
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	// ������x�N�g�����Z�b�g
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);
	//�@������������p���Z�b�g
	void SetFovY(float fovY);
	// �A�X�y�N�g����Z�b�g
	void SetAspect(float aspect);
	// ��O�̕\�����E���Z�b�g
	void SetNearClip(float nearclip);
	// ���̕\�����E���Z�b�g
	void SetFarClip(float farclip);

protected:
	DirectX::SimpleMath::Matrix m_view;		// �r���[�s��
	DirectX::SimpleMath::Matrix m_proj;		// �ˉe�s��
	
	DirectX::SimpleMath::Vector3 m_eyepos;	//���_���W(�J�����̈ʒu)
	DirectX::SimpleMath::Vector3 m_refpos;	//�����_/�Q�Ɠ_(�ǂ����݂Ă��邩)
	DirectX::SimpleMath::Vector3 m_upvec;	//������x�N�g��

	float m_fovY;		// ������������p
	float m_aspect;		// ��ʉ����Əc���̔䗦(�A�X�y�N�g��)
	float m_nearclip;	// ��ʎ�O�̕\�����E
	float m_farclip;	// ��ʉ��̕\�����E

};