//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@
//
//���t�@
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//==================================
//*�֐��̊T�v�@�R���X�g���N�^
//*����[int,int] ��ʂ̏c�A���̃T�C�Y
//*�߂�l
//==================================
Camera::Camera(int width,int height)
{
	// �����o�ϐ��̏�����
	m_eyepos = Vector3(0.0f, 0.0f, 5.0f);	//���_���W(�J�����̈ʒu)
	m_refpos = Vector3(0.0f, 0.0f, 0.0f);	//�����_/�Q�Ɠ_(�ǂ����݂Ă��邩)
	m_upvec = Vector3(0.0f, 1.0f, 0.0f);	//������x�N�g��
	m_upvec.Normalize();

	m_fovY = XMConvertToRadians(60.0f);		// ������������p
	m_aspect = float(width) / height;		// ��ʉ����Əc���̔䗦(�A�X�y�N�g��)
	m_nearclip = 0.1f;						// ��ʎ�O�̕\�����E
	m_farclip = 1000.0f;					// ��ʉ��̕\�����E

	// �r���[�s��𐶐�
	m_view = Matrix::CreateLookAt(m_eyepos,m_refpos,m_upvec);
	// �ˉe�s��𐶐�
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

//==================================
//*�֐��̊T�v�@�f�X�g���N�^
//*����[]
//*�߂�l
//==================================
Camera::~Camera()
{

}

//==================================
//*�֐��̊T�v�@�X�V����
//*����[]
//*�߂�l
//==================================
void Camera::Update()
{
	// �r���[�s��𐶐�
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	// �ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

//==================================
//*�֐��̊T�v�@�r���[�s����擾
//*����[]
//*�߂�l�@�r���[�s��
//==================================
const DirectX::SimpleMath::Matrix& Camera::GetVeiw()
{
	return m_view;
}

//==================================
//*�֐��̊T�v�@�ˉe�s����擾
//*����[]
//*�߂�l�@�ˉe�s��
//==================================
const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}

//==================================
//*�֐��̊T�v�@���_���W���Z�b�g
//*����[Vector3]�@���_���W
//*�߂�l
//==================================
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}

//==================================
//*�֐��̊T�v�@�����_���Z�b�g
//*����[Vector3]�@�����_���W
//*�߂�l
//==================================
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}

//==================================
//*�֐��̊T�v�@������x�N�g�����Z�b�g
//*����[Vector3]�@������x�N�g��
//*�߂�l
//==================================
void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

//==================================
//*�֐��̊T�v�@������������p���Z�b�g
//*����[float]�@����p
//*�߂�l
//==================================
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

//==================================
//*�֐��̊T�v�@��ʔ䗦(�A�X�y�N�g��)���Z�b�g
//*����[float]�@�䗦
//*�߂�l
//==================================
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//==================================
//*�֐��̊T�v�@��O�̕\�����E���Z�b�g
//*����[float]�@�\�����E�l
//*�߂�l
//==================================
void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

//==================================
//*�֐��̊T�v�@���̕\�����E���Z�b�g
//*����[float]�@�\�����E�l
//*�߂�l
//==================================
void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}
