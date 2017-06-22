//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　衝突判定ライブラリ
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

// 球
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	// 中心座標
	float Radius;							// 半径

	// コンストラクタ
	Sphere() {
		Radius = 1.0f;	// デフォルト半径を1m
	}
};

// 線分
class Segmrnt
{
public:
	DirectX::SimpleMath::Vector3 Start;		// 始点座標
	DirectX::SimpleMath::Vector3 End;		// 終点座標
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
