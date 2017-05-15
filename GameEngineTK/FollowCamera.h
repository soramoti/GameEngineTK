//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　自機に追従するカメラクラスのヘッダ
//
//日付　
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	static const float CAMERA_DISTANCE;		// カメラと自機の距離

	FollowCamera(int width, int height);
	~FollowCamera();

	// 更新処理
	void Update() override;

	// 追従対象座標のセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	// 追従対象角度のセット
	void SetTargetAngle(float targetAngle);

protected:
	DirectX::SimpleMath::Vector3 m_targetPos;	// 追従対象の座標
	float m_targetAngle;						// 追従対象の角度
};