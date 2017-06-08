//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//概要　自機に追従するカメラクラス
//
//日付　2017/05/16
//
//制作　Mai Kudo
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

#pragma once

#include "Camera.h"
#include <Keyboard.h>

#include "Player.h"

class FollowCamera : public Camera
{
public:
	static const float CAMERA_DISTANCE;		// カメラと自機の距離

	FollowCamera(int width, int height);
	~FollowCamera();

	// 更新処理
	void Update() override;

	// TPS視点の初期化
	void InitializeTPS();

	// 追従対象座標のセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	// 追従対象角度のセット
	void SetTargetAngle(float targetAngle);

	// キーボードをセットする（仮）
	void SetKeyboard(DirectX::Keyboard* keyboard);

	// プレイヤーのセット
	void SetPlayer(Player* player) { m_player = player; }

protected:
	DirectX::SimpleMath::Vector3 m_targetPos;	// 追従対象の座標
	float m_targetAngle;						// 追従対象の角度

	// キーボード（仮）
	DirectX::Keyboard* m_keyboard;
	// キーボードトラッカー（仮）
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	int m_keyflag;

	Player* m_player;
};