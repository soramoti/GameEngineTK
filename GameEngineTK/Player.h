//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//�T�v�@�v���C���[�N���X
//
//����@Mai Kudo
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>

#include "Obj3D.h"
#include "CollisionNode.h"

class Player
{
public:
	enum PARTS
	{
		BODY,
		FRFOOT,
		FLFOOT,
		BRFOOT,
		BLFOOT,
		HEAD,
		RWING,
		LWING,
		TAIL,
		STAR,
		STAR2,

		NUM,
	};

public:
	Player();
	~Player();

	void Initiarize();
	void Update();
	void Rebder();

	void Calc();

	void fireBullet();
	void resetBullet();


	// �L�[�{�[�h���Z�b�g����i���j
	void SetKeyboard(DirectX::Keyboard* keyboard);

	void SetPos(const DirectX::SimpleMath::Vector3& pos) { m_obj[BODY].SetTranslation(pos); }
	void SetAngle(const DirectX::SimpleMath::Vector3& angle) { m_obj[BODY].SetTranslation(angle); }

	const DirectX::SimpleMath::Vector3& GetPos(){ return m_obj[BODY].GetTranslation(); }
	const DirectX::SimpleMath::Vector3& GetAngle() { return m_obj[BODY].GetRotation(); }

	void SetClearFlag() { m_clearFlag = true; }

	const SphereNode& GetCollisionNodeBullet() { return m_collisionNodeBullet; }
private:
	// �L�[�{�[�h�i���j
	DirectX::Keyboard* m_keyboard;
	// �L�[�{�[�h�g���b�J�[�i���j
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	std::vector<Obj3D> m_obj;

	Obj3D m_clearPanel;

	bool m_clearFlag;

	float m_angle;

	float m_cycle;
	float m_wingPcycle;
	float m_wingNcycle;

	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_RwingRota;
	DirectX::SimpleMath::Vector3 m_LwingRota;
	DirectX::SimpleMath::Vector3 m_tailRota;

	DirectX::SimpleMath::Vector3 m_bulletVel;

	bool m_bulletFlag;

	int m_timer;

	// �����蔻�苅
	SphereNode m_collisionNodeBullet;
};

