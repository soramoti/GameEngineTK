//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@3D�I�u�W�F�N�g�N���X
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <windows.h>
#include <wrl/client.h>
#include <memory.h>
#include <Effects.h>
#include <CommonStates.h>
#include <Model.h>
#include <map>

#include "Camera.h"

class Obj3D
{
	// �ÓI�����o
public:
	// �ݒ�
	struct Defs
	{
		Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
		Camera* pCamera;

		Defs()
		{
			pDevice = nullptr;
			pDeviceContext = nullptr;
			pCamera = nullptr;
		}
	};
	// �ÓI�����o�֐�
	// �ÓI������
	static void StaticInitialize(const Defs& def);
	// �f�o�C�X��setter
	static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> pDevice) { m_d3dDevice = pDevice; }
	// �f�o�C�X�R���e�L�X�g��setter
	static void SetDeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext) { m_d3dContext = pDeviceContext; }
	// �J������setter
	static void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_d3dContext; }
	// ���Z�`��ݒ���Z�b�g
	static void SetSubtractive();
private:
	// �J����
	static Camera* m_pCamera;
	// �ėp�X�e�[�g
	static std::unique_ptr<DirectX::CommonStates> m_states;
	// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	// �R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	// �G�t�F�N�g�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	// �ǂݍ��ݍς݃��f���R���e�i
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> m_modelarray;
	
	static ID3D11BlendState* s_pBlendStateSubtract;
public:
	Obj3D();

	// ���f���̓ǂݍ���
	void LoadModel(const wchar_t* fileName);

	void Update();
	void Render();

	// �I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
	void DisableLighting();

	// setter(�X�P�[�����O�p�A��](�I�C���[�p)�p�A��](�N�H�[�^�j�I��)�p�A���s�ړ��p�A�e�I�u�W�F�N�g�p)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation;  m_useQuate = false; }
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotation) { m_rotationQ = rotation; m_useQuate = true; };
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation){ m_translation = translation; }
	void SetObjParent(Obj3D* objParent) { m_objParent = objParent; }
	// getter(�X�P�[�����O�p�A��]�p�A���s�ړ��p�A���[���h�s��A�e�I�u�W�F�N�g�p)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	Obj3D* GetObjParent() { return m_objParent; }
private:
	// ���f���f�[�^�ւ̃|�C���^
	const DirectX::Model* m_model;	
	// �X�P�[�����O
	DirectX::SimpleMath::Vector3 m_scale;
	// ��](�I�C���[�p)
	DirectX::SimpleMath::Vector3 m_rotation;
	// ��]�p�i�N�H�[�^�j�I���j
	DirectX::SimpleMath::Quaternion m_rotationQ;
	// ���s�ړ�
	DirectX::SimpleMath::Vector3 m_translation;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �e�ƂȂ�3D�I�u�W�F�N�g�N���X�̃|�C���^
	Obj3D* m_objParent;

	// ��]���N�H�[�^�ɂ����Ŏ����Ă���t���O
	bool m_useQuate;
};