#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
// �ÓI�����o�ϐ��̎���====
// �J����
Camera* Obj3D::m_pCamera;		
// �ėp�X�e�[�g
std::unique_ptr<DirectX::CommonStates> Obj3D::m_states;
// �f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device> Obj3D::m_d3dDevice;
// �R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3D::m_d3dContext;
// �G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Obj3D::m_factory;

void Obj3D::InitializeStatic(Camera * pCamera, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_pCamera = pCamera;
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	//�@�X�e�[�g�̐ݒ�
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	// �G�t�F�N�g�t�@�N�g���̐ݒ�
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	m_factory->SetDirectory(L"Resources");

}

Obj3D::Obj3D()
{
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_objParent = nullptr;
}

void Obj3D::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3D::Update()
{
	// �s����v�Z���鏈��=======
	// �X�P�[�����O�s��
	Matrix scaling = Matrix::CreateScale(m_scale);
	// ��]�s��
	Matrix rotaZ = Matrix::CreateRotationZ(m_rotation.z);
	Matrix rotaX = Matrix::CreateRotationX(m_rotation.x);
	Matrix rotaY = Matrix::CreateRotationY(m_rotation.y);
	Matrix rotation = rotaZ * rotaX * rotaY;
	// ���s�ړ��s��
	Matrix transrate = Matrix::CreateTranslation(m_transration);
	// ���[���h�s�������
	m_world = scaling * rotation * transrate;
	if (m_objParent)
	{
		m_world *= m_objParent->GetWorld();
	}
}

void Obj3D::Render()
{
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_pCamera->GetVeiw(), m_pCamera->GetProj());
	}
}