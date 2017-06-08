#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;		// カメラと自機の距離

FollowCamera::FollowCamera(int width, int height)
	: Camera(width,height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	m_keyflag = 0;
	InitializeTPS();
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	// キーボードの状態を取得（仮）
	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboardTracker.Update(keystate);

	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		// フラグを切り替え
		m_keyflag = (m_keyflag + 1) % 2;
		if (m_keyflag == 0)
		{
			InitializeTPS();
		}
	}

	// 追従対象の座標の設定
	SetTargetPos(m_player->GetPos());
	SetTargetAngle(m_player->GetAngle().y);


	if (m_keyflag == 0)
	{
		 //TPS視点=====
		// 自機の上方(2m)の位置をとらえる
		refpos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);
		// 参照点から視点への差分
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
		// 自機の後ろに回り込むための回転
		Matrix rotation = Matrix::CreateRotationY(m_targetAngle);
		// 差分ベクトルを回転
		cameraV = Vector3::TransformNormal(cameraV, rotation);
		// 視点座標を計算
		eyepos = refpos + cameraV;

		// 視点を現在位置から補間
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.1f;
		// 参照点を現在位置から補間
		refpos = m_refpos + (refpos - m_refpos) * 0.1f;
	}
	else
	{
		// FPS視点=====
		Vector3 upEyepos;
		// 自機の上方の位置にカメラを置く
		upEyepos = m_targetPos + Vector3(0.0f, 0.2f, 0.0f);
		// 参照点から視点への差分
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
		// 自機の後ろに回り込むための回転
		Matrix rotation = Matrix::CreateRotationY(m_targetAngle);
		// 差分ベクトルを回転
		cameraV = Vector3::TransformNormal(cameraV, rotation);
		eyepos = upEyepos + cameraV * 0.1f;
		// 参照点座標を計算
		refpos = eyepos + cameraV;
	}


	SetEyePos(eyepos);
	SetRefPos(refpos);

	// 基底クラスの更新
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	//TPS視点=====
	// 自機の上方(2m)の位置をとらえる
	refpos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);
	// 参照点から視点への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	// 自機の後ろに回り込むための回転
	Matrix rotation = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	// 差分ベクトルを回転
	cameraV = Vector3::TransformNormal(cameraV, rotation);
	// 視点座標を計算
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
