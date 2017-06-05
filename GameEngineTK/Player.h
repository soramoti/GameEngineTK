#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>

#include "Obj3D.h"

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

		NUM,
	};

public:
	Player();
	~Player();

	void Initiarize();
	void Update();
	void Rebder();

	// キーボードをセットする（仮）
	void SetKeyboard(DirectX::Keyboard* keyboard);

	const DirectX::SimpleMath::Vector3 GetPos(){ return m_objPlayer[BODY].GetTransration(); }
	const DirectX::SimpleMath::Vector3 GetAngle() { return m_objPlayer[BODY].GetRotation(); }

private:
	// キーボード（仮）
	DirectX::Keyboard* m_keyboard;

	std::vector<Obj3D> m_objPlayer;		// プレイヤー

	float m_angle;

	float m_cycle;
	float m_wingPcycle;
	float m_wingNcycle;

	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_RwingRota;
	DirectX::SimpleMath::Vector3 m_LwingRota;
	DirectX::SimpleMath::Vector3 m_tailRota;

};

