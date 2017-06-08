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

	// setter(�X�P�[�����O�p�A��]�p�A���s�ړ��p�A�e�I�u�W�F�N�g�p)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation){ m_rotation = rotation; }
	void SetTransration(const DirectX::SimpleMath::Vector3& transration){ m_transration = transration; }
	void SetObjParent(Obj3D* objParent) { m_objParent = objParent; }
	// getter(�X�P�[�����O�p�A��]�p�A���s�ړ��p�A���[���h�s��A�e�I�u�W�F�N�g�p)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	const DirectX::SimpleMath::Vector3& GetTransration() { return m_transration; }
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	Obj3D* GetObjParent() { return m_objParent; }
private:
	// 3D���f���̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;
	// �X�P�[�����O
	DirectX::SimpleMath::Vector3 m_scale;
	// ��]
	DirectX::SimpleMath::Vector3 m_rotation;
	// ���s�ړ�
	DirectX::SimpleMath::Vector3 m_transration;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �e�ƂȂ�3D�I�u�W�F�N�g�N���X�̃|�C���^
	Obj3D* m_objParent;
};