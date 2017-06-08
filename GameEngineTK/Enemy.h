#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>

#include "Obj3D.h"

class Enemy
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
	Enemy();
	~Enemy();

	void Initiarize();
	void Update();
	void Rebder();

	void SetPos(const DirectX::SimpleMath::Vector3& pos) { m_obj[BODY].SetTransration(pos); }
	void SetAngle(const DirectX::SimpleMath::Vector3& angle) { m_obj[BODY].SetRotation(angle); }

	const DirectX::SimpleMath::Vector3& GetPos(){return m_obj[BODY].GetTransration();}
	const DirectX::SimpleMath::Vector3& GetAngle() { return m_obj[BODY].GetRotation(); }

private:
	std::vector<Obj3D> m_obj;

	float m_angle;

	float m_cycle;
	float m_wingPcycle;
	float m_wingNcycle;

	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_RwingRota;
	DirectX::SimpleMath::Vector3 m_LwingRota;
	DirectX::SimpleMath::Vector3 m_tailRota;

	int m_timer;
	float m_distAngle;
};

