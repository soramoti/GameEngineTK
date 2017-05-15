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
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	// 追従カメラ====
	Vector3 eyepos, refpos;
	// 自機の上方2mの位置をとらえる
	refpos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);
	// 参照点から視点への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	// 
	Matrix rotation = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	// 差分ベクトルを回転
	cameraV = Vector3::TransformNormal(cameraV, rotation);
	// 視点座標を計算
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);

	// 基底クラスの更新
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}
