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

}

void Obj3D::LoadModel(const wchar_t * fileName)
{
}

void Obj3D::Update()
{
}

void Obj3D::Render()
{
}

void Obj3D::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	m_scale = scale;
}

void Obj3D::SetRotation(float rotation)
{
	m_rotation = rotation;
}

void Obj3D::SetTransration(DirectX::SimpleMath::Vector3 transration)
{
	m_transration = transration;
}

DirectX::SimpleMath::Vector3 Obj3D::GetScale()
{
	return m_scale;
}

float Obj3D::GetRotation()
{
	return m_rotation;
}

DirectX::SimpleMath::Vector3 Obj3D::GetTransration()
{
	return m_transration;
}

DirectX::SimpleMath::Matrix Obj3D::GetWorld()
{
	return m_world;
}
