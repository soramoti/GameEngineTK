//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@3D�I�u�W�F�N�g�N���X
//
//���t�@
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

#include "Camera.h"

class Obj3D
{
	// �ÓI�����o
public:
	// �ÓI�����o�̏�����
	static void InitializeStatic(Camera* pCamera, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);
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

public:
	Obj3D();

	// ���f���̓ǂݍ���
	void LoadModel(const wchar_t* fileName);

	void Update();
	void Render();

	// setter(�X�P�[�����O�p�A��]�p�A���s�ړ��p)
	void SetScale(DirectX::SimpleMath::Vector3 scale);
	void SetRotation(float rotation);
	void SetTransration(DirectX::SimpleMath::Vector3 transration);

	// getter(�X�P�[�����O�p�A��]�p�A���s�ړ��p�A���[���h�s��)
	DirectX::SimpleMath::Vector3 GetScale();
	float GetRotation();
	DirectX::SimpleMath::Vector3 GetTransration();
	DirectX::SimpleMath::Matrix GetWorld();
private:
	// 3D���f���̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;
	// �X�P�[�����O
	DirectX::SimpleMath::Vector3 m_scale;
	// ��]
	float m_rotation;
	// ���s�ړ�
	DirectX::SimpleMath::Vector3 m_transration;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �e�ƂȂ�3D�I�u�W�F�N�g�N���X�̃|�C���^
	Obj3D* m_obj;
};